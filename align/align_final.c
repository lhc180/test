#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
/*
	这里的len偏移是否有问题？
	将地址从偶地址开始，避免数据拼凑带来的效率下降
 */

#define RASTER_OP(_name, _equation)						    \
	static void solid_rop_ ## _name(void* ptr, int val, uint32_t len)		    \
{										    \
	uint32_t	src;								    \
	uint32_t	dst;								    \
	\
	src	=   val;								    \
	if (((int)ptr & 0x01) && (len >= 1)){					    \
		dst		    =	*((uint8_t*)(ptr));				    \
		*((uint8_t*)(ptr))  =	(uint8_t)(_equation);				    \
		src		    =	(src >> 8) | (src << 24);			    \
		ptr		    =	(void*)((int)(ptr) + 1);			    \
		len		    -=	1;						    \
	}										    \
	if (((int)ptr & 0x02) && (len >= 2)){					    \
		dst		    =	*((uint16_t*)(ptr));				    \
		*((uint16_t*)(ptr)) =	(uint16_t)(_equation);				    \
		src		    =	(src << 16) | (src >> 16);			    \
		ptr		    =	(void*)((int)(ptr) + 2);			    \
		len		    -=	2;						    \
	}										    \
	while(len >= 4){								    \
		dst		    =	*((uint32_t*)(ptr));				    \
		*((uint32_t*)(ptr)) =	(uint32_t)(_equation);				    \
		ptr		    =	(void*)((int)(ptr) + 4);			    \
		len		    -=	4;						    \
	}										    \
	\
	/*	至此，DST至少是按2byte对齐的	:   不然进函数时(len == 0)，此时无任何操作  \
	 */										    \
	if (len >= 2){								    \
		dst		    =	*((uint16_t*)(ptr));				    \
		src		    =	(src << 16) | (src >> 16);			    \
		*((uint16_t*)(ptr)) =	(uint16_t)(_equation);				    \
		ptr		    =	(void*)((int)(ptr) + 2);			    \
		len		    -=	2;						    \
	}										    \
	if (len >= 1){								    \
		dst		    =	*((uint8_t*)(ptr));				    \
		src		    =	(src >> 8) | (src << 24);			    \
		*((uint8_t*)(ptr))  =	(uint8_t)(_equation);				    \
		ptr		    =	(void*)((int)(ptr) + 1);			    \
		len		    -=	1;						    \
	}										    \
	return;									    \
}										    \
\
static void copy_rop_ ## _name(void* ptr, void* src_line, uint32_t len)		    \
{										    \
	uint32_t	src;								    \
	uint32_t	dst;								    \
	uint32_t	tmp;								    \
	uint32_t	shift;								    \
	uint32_t	next;								    \
	int			flag;									\
	\
	/*	首先将DST，按照4byte对齐    :	无法对齐时，必然(len == 0)		    \
	 */										    \
	while (((int)ptr & 0x03) && (len >= 1)){					    \
		src =	*((uint8_t*)src_line);						    \
		dst =	*((uint8_t*)ptr);						    \
		*((uint8_t*)ptr)    =	(uint8_t)(_equation);				    \
		len	    -=	1;							    \
		ptr	    =	(void*)(((int)(ptr)) + 1);				    \
		src_line    =	(void*)(((int)(src_line)) + 1);				    \
	}										    \
	/*	此时DST已经4byte对齐，但SRC不定						    \
	 */										    \
	if ((int)src_line & 0x03){							    \
		if (len >= 4){								    \
			tmp	    =   0;							    \
			shift   =   0;							    \
			flag	=   0;								\
			\
			/*	把SRC按4byte对齐，与DST时的错位部分，暂存于tmp变量		    \
			 */								    \
			if ((int)src_line & 0x01){						    \
				tmp	    =   tmp << 8 | (*((uint8_t*)(src_line)));		    \
				shift	    +=  8;						    \
				src_line    =   (void*)(((int)(src_line)) + 1);			    \
				len	    -=	1;						    \
				flag	= 1;								\
				printf("1\n");							\
			}									    \
			if ((int)src_line & 0x02){						    \
				tmp	    =  (*((uint16_t*)(src_line))<< (8*(flag))) | tmp * flag;	    \
				shift	    +=	16;						    \
				src_line    =   (void*)(((int)(src_line)) + 2);			    \
				len	    -=	2;						    \
				printf("2\n");							\
			}									    \
			while(len >= 4){							    \
				next		    =   *((uint32_t*)(src_line));		    \
				src		    =   tmp | (next << shift);    \
				dst		    =   *((uint32_t*)ptr);			    \
				*((uint32_t*)(ptr)) =	(_equation);				    \
				ptr		    =   (void*)(((int)(ptr)) + 4);		    \
				src_line	    =   (void*)(((int)(src_line)) + 4);		    \
				len		    -=  4;					    \
				tmp		    =   next >> (32 -shift);					    \
			}									    \
			/*	把错位部分复制至DST，此时SRC按4byte对齐，但是DST不对齐		    \
			 */									    \
			if (shift & 0x10){							    \
				src		    =   (uint16_t)(tmp >> (shift - 16));	    \
				dst		    =   *((uint16_t*)ptr);			    \
				*((uint16_t*)ptr)   =	(uint16_t)(_equation);			    \
				ptr		    =	(void*)(((int)(ptr)) + 2);		    \
			}									    \
			if (shift & 0x08){							    \
				src		    =   (uint8_t)(tmp);				    \
				dst		    =   *((uint8_t*)ptr);			    \
				*((uint8_t*)ptr)   =	(uint8_t)(_equation);			    \
				ptr		    =	(void*)(((int)(ptr)) + 1);		    \
			}									    \
		}									    \
	}else{									    \
		while(len >= 4){							    \
			src			=   *((uint32_t*)src_line);			    \
			dst			=   *((uint32_t*)ptr);				    \
			*((uint32_t*)ptr)	=   (_equation);				    \
			ptr			=   (void*)(((int)(ptr)) + 4);			    \
			src_line		=   (void*)(((int)(src_line)) + 4);		    \
			len			-=  4;						    \
		}									    \
	}										    \
	\
	while (len){								    \
		src =	*((uint8_t*)src_line);						    \
		dst =	*((uint8_t*)ptr);						    \
		*((uint8_t*)ptr)    =	(uint8_t)(_equation);				    \
		len	    -=	1;							    \
		ptr	    =	(void*)(((int)(ptr)) + 1);				    \
		src_line    =	(void*)(((int)(src_line)) + 1);				    \
	}										    \
	return;									    \
}										    \
\
\
static void tile_rop_ ## _name(void* ptr, uint32_t len, void* tile, void* tile_end, uint32_t tile_width)   \
{													    \
	int		shift;											    \
	uint32_t	concat;											    \
	void*	tile_tail;										    \
	void*	tile_head;										    \
	int		hi_shift;										    \
	int		lo_shift;										    \
	uint32_t	hi;											    \
	uint32_t	lo;											    \
	uint32_t	next;											    \
	uint32_t	src;											    \
	uint32_t	dst;											    \
	\
	tile_head	=   (void*)((uint8_t*)tile_end - tile_width);						    \
	tile_tail   =   (void*)((int)tile_end & (~0x03));							    \
	\
	/*	首先将DST，按照4byte对齐    :	无法对齐时，必然(len == 0)					    \
	 */													    \
	while (((int)ptr & 0x03) && (len >= 1)){									    \
		src =	*((uint8_t*)tile);									    \
		dst =	*((uint8_t*)ptr);									    \
		*((uint8_t*)ptr)    =	(uint8_t)(_equation);							    \
		len	-=  1;											    \
		ptr	=   (void*)(((int)(ptr)) + 1);								    \
		tile	=   (void*)(((int)(tile)) + 1);								    \
		if (tile == tile_end){										    \
			tile    =	tile_head;									    \
		}												    \
	}													    \
	\
	hi		=   0;											    \
	hi_shift    =   0;											    \
	lo		=   0;											    \
	lo_shift    =   0;											    \
	\
	/*	首尾两部分  :											    \
	 *	1)  要么包含一个完整的tile行，对应于tile太小，不足4byte的情况					    \
	 *	2)  要么至对齐处，对应于一般情况								    \
	 */													    \
	if ((int)tile_end & 0x03){										    \
		do{												    \
			lo  << 8;											\
			lo	|=  (*((uint8_t*)(tile_end) - lo_shift - 1));			    \
			lo_shift++;											    \
		}while((((int)(tile_end) - lo_shift) > (int)(tile_head)) && (((int)(tile_end) - lo_shift) & 0x03)); \
		lo_shift    <<=	3;										    \
	}													    \
	if ((int)tile_head & 0x03){										    \
		while(((int)(tile_head) + hi_shift) < ((int)(tile_end)) && (((int)(tile_head) + hi_shift) & 0x03)){ \
			hi	|=  (*((uint8_t*)(tile_head) + hi_shift)) << (hi_shift << 3);						    \
			hi_shift++;											    \
		}												    \
		hi_shift    <<=	3;										    \
		tile_head   =	(void*)(((int)tile_head + 0x03 ) & (~0x03));					    \
	}													    \
	\
	concat  =	0;											    \
	shift   =	0;											    \
	\
	if ((int)tile & 0x03){											    \
		while((tile < tile_end) && ((int)tile & 0x03)){							    \
			concat  |=  *((uint8_t*)(tile)) << shift;								    \
			tile    =   (void*)((int)tile + 1);								    \
			shift   +=  8;										    \
		}												    \
	}													    \
	\
	pattern:												    \
	if (shift){												    \
		while((len >= 4) && (tile < tile_tail)){							    \
			next	=   *((uint32_t*)(tile));							    \
			src		=   concat | (next << shift);					    \
			dst		=   *((uint32_t*)(ptr));							    \
			*((uint32_t*)(ptr))	=   (uint32_t)(_equation);						    \
			ptr		=   (void*)(((int)(ptr)) + 4);							    \
			tile	=   (void*)(((int)(tile)) + 4);							    \
			len		-=  4;										    \
			concat	=   next >> (32 - shift);									    \
		}												    \
	}else{												    \
		while((len >= 4) && (tile < tile_tail)){							    \
			src		=   *((uint32_t*)(tile));							    \
			dst		=   *((uint32_t*)(ptr));							    \
			*((uint32_t*)(ptr))	=   (uint32_t)(_equation);						    \
			ptr		=   (void*)(((int)(ptr)) + 4);							    \
			tile	=   (void*)(((int)(tile)) + 4);							    \
			len		-=  4;										    \
		}												    \
	}													    \
	if (tile < tile_end){										    \
		if ((shift + lo_shift) >= 32){									    \
			concat	|=  lo << shift;								    \
			shift	=   32;										    \
			if (len >= 4){										    \
				src		    =   concat;								    \
				dst		    =   *((uint32_t*)(ptr));						    \
				*((uint32_t*)(ptr)) =   (uint32_t)(_equation);						    \
				ptr		    =   (void*)(((int)(ptr)) + 4);					    \
				len		    -=  4;								    \
				concat		    =   lo >> (32 - shift);						    \
				shift		    =   lo_shift - (32 - shift);					    \
			}												    \
		}else{												    \
			concat  |=  lo << shift;							    \
			shift   +=  lo_shift;									    \
		}												    \
	}													    \
	if ((shift + hi_shift) >= 32){									    \
		concat  <<= (32 - shift);									    \
		concat  |=  hi >> ((hi_shift + shift) - 32);							    \
		if (len >= 4){											    \
			src		    =   concat;									    \
			dst		    =   *((uint32_t*)(ptr));							    \
			*((uint32_t*)(ptr)) =   (uint32_t)(_equation);						    \
			ptr		    =   (void*)(((int)(ptr)) + 4);						    \
			len		    -=  4;									    \
			concat	    =   hi;									    \
			shift	    =   (lo_shift + shift) - 32;						    \
		}												    \
	}else{												    \
		concat  |=  hi << shift;											    \
		shift   +=	hi_shift;									    \
	}													    \
	if (len >= 4){											    \
		tile    =	tile_head;									    \
		goto pattern;											    \
	}													    \
	if (len & 0x02){											    \
		src	=   *((uint16_t*)(&concat));								    \
		dst	=   *((uint16_t*)ptr);									    \
		*((uint16_t*)ptr)    =  (uint16_t)(_equation);							    \
		len	-=  2;											    \
		ptr	=   (void*)(((int)(ptr)) + 2);								    \
		concat  >>=	16;										    \
	}													    \
	if (len & 0x01){											    \
		src	=   *((uint8_t*)(&concat));								    \
		dst	=   *((uint8_t*)ptr);									    \
		*((uint8_t*)ptr)    =  (uint8_t)(_equation);							    \
		len	-=	1;										    \
		ptr	=   (void*)(((int)(ptr)) + 1);								    \
		concat  <<=	8;										    \
	}													    \
	return;												    \
}

	RASTER_OP(clear, 0x0)
	RASTER_OP(and, src & dst)
	RASTER_OP(and_reverse, src & ~dst)
	RASTER_OP(copy, src)
	RASTER_OP(and_inverted, ~src & dst)
	RASTER_OP(noop, dst)
	RASTER_OP(xor, src ^ dst)
	RASTER_OP(or, src | dst)
	RASTER_OP(nor, ~src & ~dst)
	RASTER_OP(equiv, ~src ^ dst)
	RASTER_OP(invert, ~dst)
	RASTER_OP(or_reverse, src | ~dst)
	RASTER_OP(copy_inverted, ~src)
	RASTER_OP(or_inverted, ~src | dst)
	RASTER_OP(nand, ~src | ~dst)
	RASTER_OP(set, 0xffffffff)

#if 0
	typedef void (*solid_rop_func_t)(uint8_t* ptr, uint32_t val, int len);
	typedef void (*solid_rop_func_t)(uint16_t* ptr, uint32_t val, int len);
	typedef void (*solid_rop_func_t)(uint32_t* ptr, uint32_t val, int len);
	typedef void (*copy_rop_func_t)(uint8_t* ptr, void* src, int len);
	typedef void (*copy_rop_func_t)(uint16_t* ptr, void* src, int len);
	typedef void (*copy_rop_func_t)(uint32_t* ptr, void* src, int len);
	typedef void (*tiled_rop_func_t)(uint8_t* ptr, int len, void* tile, void* tile_end, int tile_width);
	typedef void (*tiled_rop_func_t)(uint16_t* ptr, int len, void* tile, void* tile_end, int tile_width);
	typedef void (*tiled_rop_func_t)(uint32_t* ptr, int len, void* tile, void* tile_end, int tile_width);
#endif
	typedef void (*solid_rop_func_t)(void* ptr, int val, uint32_t len);
	typedef void (*copy_rop_func_t)(void* ptr, void* src, uint32_t len);
	typedef void (*tiled_rop_func_t)(void* ptr, uint32_t len, void* tile, void* tile_end, uint32_t tile_width);

#define ROP_TABLE                                                 \
		static void (*solid_rops[16]) (void* ptr, int val, uint32_t len) = {		\
			solid_rop_clear,								\
			solid_rop_and,								\
			solid_rop_and_reverse,							\
			solid_rop_copy,								\
			solid_rop_and_inverted,							\
			solid_rop_noop,								\
			solid_rop_xor,								\
			solid_rop_or,								\
			solid_rop_nor,								\
			solid_rop_equiv,								\
			solid_rop_invert,								\
			solid_rop_or_reverse,							\
			solid_rop_copy_inverted,							\
			solid_rop_or_inverted,							\
			solid_rop_nand,								\
			solid_rop_set								\
		};										\
	static void (*copy_rops[16]) (void* ptr, void* src, uint32_t len) = {		\
		copy_rop_clear,								\
		copy_rop_and,								\
		copy_rop_and_reverse,							\
		copy_rop_copy,								\
		copy_rop_and_inverted,							\
		copy_rop_noop,								\
		copy_rop_xor,								\
		copy_rop_or,								\
		copy_rop_nor,								\
		copy_rop_equiv,								\
		copy_rop_invert,								\
		copy_rop_or_reverse,							\
		copy_rop_copy_inverted,							\
		copy_rop_or_inverted,							\
		copy_rop_nand,								\
		copy_rop_set								\
	};										\
	static void (*tile_rops[16]) (void* ptr, uint32_t len, void* tile, void* tile_end, uint32_t tile_width) = {	    \
		tile_rop_clear,								\
		tile_rop_and,								\
		tile_rop_and_reverse,							\
		tile_rop_copy,								\
		tile_rop_and_inverted,							\
		tile_rop_noop,								\
		tile_rop_xor,								\
		tile_rop_or,								\
		tile_rop_nor,								\
		tile_rop_equiv,								\
		tile_rop_invert,								\
		tile_rop_or_reverse,							\
		tile_rop_copy_inverted,							\
		tile_rop_or_inverted,							\
		tile_rop_nand,								\
		tile_rop_set								\
	};										\

ROP_TABLE

int main(int argc, char** argv)
{
	void*   dst;
	void*   src;
	int	i;
	uint8_t		data1 = 0x12;
	uint16_t	data2 = 0x3456;
	uint32_t	data  = 0;

	dst	=   malloc(4 * 1024 * 1024);
	src	=   malloc(4 * 1024);
	memset(src, 0, 4 * 1024);
	memset(dst, 0, 4 * 1024 * 1024);
	printf("\ndst addr at %p\nsrc addr at %p\n", dst, src); 
	
	data = data2|data2<<16;

	data = 0x12345678;
	printf("data: 0x%x\n", data);

	solid_rop_func_t rop_func = solid_rops[3];
	rop_func((uint32_t*)(src+1), data, 4*1024-1);
	for (i=0; i<32; i++){
		printf("0x%2x ", *((uint8_t*)src + i));
	}


	printf("src+1: %p\n", (src+1));
	solid_rop_copy((uint32_t*)(src+1), data, 4*1024-1);
	printf("solid done\n");
	for (i=0; i<32; i++){
		printf("0x%2x ", *((uint8_t*)src + i));
	}
	printf("\n");
	copy_rop_copy((uint32_t*)dst+2, src, 4*1024);
	printf("copy done\n");

	for (i=0; i<32; i++){
		printf("0x%2x ", *((uint8_t*)dst + i));
	}
	printf("\n");

	tile_rop_copy((uint32_t*)dst+1, 4*1024, src, src+4*1024, 1024);
	printf("tile done\n");

	for (i=0; i<32; i++){
		printf("0x%2x ", *((uint8_t*)dst + i));
	}   
	printf("\n");

	return;
}
