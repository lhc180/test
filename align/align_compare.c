#include <stdio.h>
#include <stdlib.h>
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

#define SOLID_RASTER_OP(_name, _size, _type, _equation)  \
static void                                        \
solid_rop_ ## _name ## _ ## _size (_type *ptr, int len, _type src)  \
{                                                  \
    while (len--) {                                \
        _type dst = *ptr;                          \
        if (dst) /* avoid unused warning */{};      \
        *ptr = (_type)(_equation);                 \
        ptr++;                                     \
    }                                              \
}                                                  \

#define TILED_RASTER_OP(_name, _size, _type, _equation) \
static void                                        \
tiled_rop_ ## _name ## _ ## _size (_type *ptr, int len, _type *tile, _type *tile_end, int tile_width)   \
{                                                  \
    while (len--) {                                \
        _type src = *tile;                         \
        _type dst = *ptr;                          \
        if (src) /* avoid unused warning */{};       \
        if (dst) /* avoid unused warning */{};       \
        *ptr = (_type)(_equation);                 \
        ptr++;                                     \
        tile++;                                    \
        if (tile == tile_end)                      \
            tile -= tile_width;                    \
    }                                              \
}                                                  \

#define COPY_RASTER_OP(_name, _size, _type, _equation) \
static void                                        \
 copy_rop_ ## _name ## _ ## _size (_type *ptr, _type *src_line, int len)        \
{                                                  \
    while (len--) {                                \
        _type src = *src_line;                     \
        _type dst = *ptr;                          \
        if (src) /* avoid unused warning */ {};       \
        if (dst) /* avoid unused warning */{};       \
        *ptr = (_type)(_equation);                 \
        ptr++;                                     \
        src_line++;                                \
    }                                              \
}                                                  \

#define RASTER_OP(name, equation) \
    SOLID_RASTER_OP(name, 8, uint8_t, equation) \
    SOLID_RASTER_OP(name, 16, uint16_t, equation) \
    SOLID_RASTER_OP(name, 32, uint32_t, equation) \
    TILED_RASTER_OP(name, 8, uint8_t, equation) \
    TILED_RASTER_OP(name, 16, uint16_t, equation) \
    TILED_RASTER_OP(name, 32, uint32_t, equation) \
    COPY_RASTER_OP(name, 8, uint8_t, equation) \
    COPY_RASTER_OP(name, 16, uint16_t, equation) \
    COPY_RASTER_OP(name, 32, uint32_t, equation)

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

typedef void (*solid_rop_8_func_t)(uint8_t *ptr, int len, uint8_t src);
typedef void (*solid_rop_16_func_t)(uint16_t *ptr, int len, uint16_t src);
typedef void (*solid_rop_32_func_t)(uint32_t *ptr, int len, uint32_t src);
typedef void (*tiled_rop_8_func_t)(uint8_t *ptr, int len,
                                   uint8_t *tile, uint8_t *tile_end, int tile_width);
typedef void (*tiled_rop_16_func_t)(uint16_t *ptr, int len,
                                    uint16_t *tile, uint16_t *tile_end, int tile_width);
typedef void (*tiled_rop_32_func_t)(uint32_t *ptr, int len,
                                    uint32_t *tile, uint32_t *tile_end, int tile_width);
typedef void (*copy_rop_8_func_t)(uint8_t *ptr, uint8_t *src, int len);
typedef void (*copy_rop_16_func_t)(uint16_t *ptr, uint16_t *src, int len);
typedef void (*copy_rop_32_func_t)(uint32_t *ptr, uint32_t *src, int len);

#define ROP_TABLE(_type, _size)                                                 \
static void (*solid_rops_ ## _size[16]) (_type *ptr, int len, _type src) = { \
    solid_rop_clear_ ## _size,  \
    solid_rop_and_ ## _size,    \
    solid_rop_and_reverse_ ## _size,    \
    solid_rop_copy_ ## _size,    \
    solid_rop_and_inverted_ ## _size,    \
    solid_rop_noop_ ## _size,    \
    solid_rop_xor_ ## _size,    \
    solid_rop_or_ ## _size,    \
    solid_rop_nor_ ## _size,    \
    solid_rop_equiv_ ## _size,    \
    solid_rop_invert_ ## _size,    \
    solid_rop_or_reverse_ ## _size,    \
    solid_rop_copy_inverted_ ## _size,    \
    solid_rop_or_inverted_ ## _size,    \
    solid_rop_nand_ ## _size,    \
    solid_rop_set_ ## _size    \
};                          \
static void (*tiled_rops_ ## _size[16]) (_type *ptr, int len, _type *tile, _type *tile_end, int tile_width) = { \
    tiled_rop_clear_ ## _size,  \
    tiled_rop_and_ ## _size,    \
    tiled_rop_and_reverse_ ## _size,    \
    tiled_rop_copy_ ## _size,    \
    tiled_rop_and_inverted_ ## _size,    \
    tiled_rop_noop_ ## _size,    \
    tiled_rop_xor_ ## _size,    \
    tiled_rop_or_ ## _size,    \
    tiled_rop_nor_ ## _size,    \
    tiled_rop_equiv_ ## _size,    \
    tiled_rop_invert_ ## _size,    \
    tiled_rop_or_reverse_ ## _size,    \
    tiled_rop_copy_inverted_ ## _size,    \
    tiled_rop_or_inverted_ ## _size,    \
    tiled_rop_nand_ ## _size,    \
    tiled_rop_set_ ## _size    \
}; \
static void (*copy_rops_ ## _size[16]) (_type *ptr, _type *tile, int len) = { \
    copy_rop_clear_ ## _size,  \
    copy_rop_and_ ## _size,    \
    copy_rop_and_reverse_ ## _size,    \
    copy_rop_copy_ ## _size,    \
    copy_rop_and_inverted_ ## _size,    \
    copy_rop_noop_ ## _size,    \
    copy_rop_xor_ ## _size,    \
    copy_rop_or_ ## _size,    \
    copy_rop_nor_ ## _size,    \
    copy_rop_equiv_ ## _size,    \
    copy_rop_invert_ ## _size,    \
    copy_rop_or_reverse_ ## _size,    \
    copy_rop_copy_inverted_ ## _size,    \
    copy_rop_or_inverted_ ## _size,    \
    copy_rop_nand_ ## _size,    \
    copy_rop_set_ ## _size    \
};

ROP_TABLE(uint8_t, 8)
ROP_TABLE(uint16_t, 16)
ROP_TABLE(uint32_t, 32)

int main ()
{
	uint8_t*   dst;
	uint8_t*   src;
	int i;
//	uint8_t data = 0x12;
	int data = 0x12345678;

	dst =   (uint8_t*)malloc(4 * 1024*1024);
	src =   (uint32_t*)malloc(4 * 1024);
	printf("\ndst addr at %p\nsrc addr at %p\n", dst, src);

	solid_rop_copy_32((uint8_t*)src+1, 4*1024, data);
	printf("solid done\n");
	for (i=0; i<32; i++){
		printf("0x%2x ", *((uint8_t*)src + i));
	}   
	printf("\n");
	copy_rop_copy_8((uint8_t*)dst+1, src, 4*1024);
	printf("copy done\n");

	for (i=0; i<32; i++){
		printf("0x%2x ", *((uint8_t*)dst + i));
	}   
	printf("\n");


	return;
}
