#include "common.h"
#define		SOLID	0
//#define		TILE	1
//#define		BLIT	2
//#define		BLEND	3
int main(int argc, char**argv)
{
	struct Show	*show;
	char        filename[256]; 
	char        filename2[256]; 
//	char        filename3[256]; 
	char*       data;
	char*       data2 = NULL;   
//	char*       data3 = NULL;   
	char*       buffer;
	char*       buffer2 = NULL; 
//	char*       buffer3 = NULL; 
	int         width, height, depth;  
	int         width2, height2, depth2;  
//	int         width3, height3, depth3;  
	int			event_base;
	int			error_base;
	XRenderPictFormat           *format;

	if(argc == 1){
		strcpy(filename, "./background.bmp"); 
		strcpy(filename2, "./foreground.bmp"); 
	//	strcpy(filename3, "./mask.bmp"); 
		buffer2 = (char*) malloc(4*1024*1024); 
	//	buffer3 = (char*) malloc(4*1024*1024); 
		read_bmp_file(filename2, buffer2, &data2, &width2, &height2, &depth2); 
	//	read_bmp_file(filename3, buffer3, &data3, &width3, &height3, &depth3); 
	}
	if(argc == 2) { 
		strcpy(filename, argv[1]); 
	}

	buffer = (char*) malloc(4*1024*1024); 
	if(buffer == NULL) { 
		return -1; 
	} 

	data = NULL; 
	read_bmp_file(filename, buffer, &data, &width, &height, &depth); 

	if(data == NULL) {
		free(buffer);
		return -1;
	}
	show = malloc(sizeof(struct Show));
	show->dpy		=	XOpenDisplay(NULL);
	assert(show->dpy);
	show->screen	=	DefaultScreen(show->dpy);
	show->visual	=	DefaultVisual(show->dpy, show->screen);
	show->win		=	XCreateSimpleWindow(show->dpy, RootWindow(show->dpy, show->screen), 0, 0,WIDTH, HEIGHT, 1, 0, 0xfb);
	XSelectInput(show->dpy, show->win, ExposureMask | KeyPressMask);

	XMapWindow(show->dpy, show->win);

	show->pict_src	=	malloc(sizeof(struct PictInfo));
	show->pict_dst	=	malloc(sizeof(struct PictInfo));
	show->pict_drawable	=	malloc(sizeof(struct PictInfo));

	show->pict_src->pixmap	=	XCreatePixmap(show->dpy, show->win, width2, height2, 32); 
	show->pict_dst->pixmap	=	XCreatePixmap(show->dpy, show->win, width2, height2, 32);
	show->pict_drawable->pixmap		=	XCreatePixmap(show->dpy, show->win, width2, height2, 32); 

	show->ximage_src	=	XCreateImage(show->dpy, show->visual, 32, ZPixmap, 0, data, width2, height2, 32, 0);
	printf("byte per line: %d\n", show->ximage_src->bytes_per_line);
	show->ximage_dst	=	XCreateImage(show->dpy, show->visual, 32, ZPixmap, 0, data2, width2, height2, 32, 0);

	show->width			=	width;
	show->height		=	height;
	XFlush(show->dpy);
/***********************************************************************************************/
//	XPutImage(show->dpy, show->pict_drawable->pixmap, show->gc, show->ximage_dst, 0, 0, 0, 0, width2, height2);
//	XSetFunction(show->dpy, show->gc, GXxor);
#ifdef	SOLID

	XGCValues	gcval;
	gcval.fill_style	=	FillSolid;
	show->gc	=	XCreateGC(show->dpy, show->pict_drawable->pixmap, GCFillStyle, &gcval);
	XPutImage(show->dpy, show->pict_drawable->pixmap, show->gc, show->ximage_dst, 0, 0, 0, 0, width2, height2);
	printf("dst data: 0x%x\n", show->ximage_dst->data);
	XImage *ximage = XGetImage(show->dpy,show->pict_drawable->pixmap, 0, 0, width, height, 0xffffffff, ZPixmap);
	printf("image data: 0x%x\n", ximage->data);
//	show->ximage_src = show->ximage_dst;
	memcpy(show->ximage_dst->data, ximage->data, width*height*4);
	XPutImage(show->dpy,show->pict_src->pixmap, show->gc, show->ximage_src, 0, 0, 0, 0, width, height);
	//XPutImage(show->dpy,show->pict_drawable->pixmap, show->gc, ximage, 0, 0, 0, 0, width/2, height/2);
	XCopyArea(show->dpy, show->pict_src->pixmap, show->pict_drawable->pixmap, show->gc, 0, 0, width, height, 0, 0);
	/*
	XSetForeground(show->dpy, show->gc, 0xfbfb);
	XDrawRectangle(show->dpy, show->pict_drawable->pixmap, show->gc, 0, 0, 100, 100);
	XDrawArc(show->dpy, show->pict_drawable->pixmap, show->gc, 10, 10, 400, 300, 0, 270*64);
	XSetFunction(show->dpy, show->gc, GXxor);
	XFillRectangle(show->dpy,show->pict_drawable->pixmap, show->gc, 0, 0, 200, 200);
	XSetFunction(show->dpy, show->gc, GXcopy);
	*/
#endif
#ifdef TILE
	show->gc    =   XCreateGC(show->dpy, show->pict_drawable->pixmap, 0, NULL);
	Pixmap tile		=	XCreatePixmap(show->dpy, show->win, 200, 200, 32);
	XPutImage(show->dpy, tile, show->gc, show->ximage_src, 100, 400, 0, 0, 200, 200);
	XGCValues   gcval;
	gcval.fill_style    =	FillTiled;
	gcval.tile			=	tile;
	gcval.ts_x_origin	=	10;
	gcval.ts_y_origin	=	50;
	show->gc    =   XCreateGC(show->dpy, show->pict_drawable->pixmap, GCFillStyle|GCTile|GCTileStipXOrigin|GCTileStipYOrigin, &gcval);
	//XCopyArea(show->dpy, tile, show->pict_drawable->pixmap, show->gc, 0, 0, 800, 600, 0, 0);
	XFillRectangle(show->dpy,show->pict_drawable->pixmap, show->gc, 0, 0, 800,600);

#endif
#ifdef	BLIT
	show->gc    =   XCreateGC(show->dpy, show->pict_drawable->pixmap, 0, NULL);
	XPutImage(show->dpy, show->pict_src->pixmap, show->gc, show->ximage_dst, 0, 0, 0, 0, width2, height2);
	XPutImage(show->dpy, show->pict_dst->pixmap, show->gc, show->ximage_src, 0, 0, 0, 0, width, height);

	XSetFunction(show->dpy, show->gc, GXxor);
	XCopyArea(show->dpy, show->pict_src->pixmap, show->pict_dst->pixmap, show->gc, 0, 0, width, height, 0, 0);
	XSetFunction(show->dpy, show->gc, GXcopy);
	XCopyArea(show->dpy, show->pict_dst->pixmap, show->pict_drawable->pixmap, show->gc, 0, 0, width, height,     0, 0);
#endif
#ifdef BLEND
	XRenderPictureAttributes	attr;
	attr.repeat				=	FALSE;//TRUE;
	attr.component_alpha	=	TRUE;

	show->gc    =   XCreateGC(show->dpy, show->pict_drawable->pixmap, 0, NULL);
	XPutImage(show->dpy, show->pict_src->pixmap, show->gc, show->ximage_src, 0, 0, 0, 0, width2, height2);
	printf("bytes per line %d\n", show->ximage_src->bytes_per_line);
	XPutImage(show->dpy, show->pict_dst->pixmap, show->gc, show->ximage_dst, 0, 0, 0, 0, width, height);
	format		=	XRenderFindStandardFormat(show->dpy, PictStandardARGB32);
	show->pict_src->picture	=	XRenderCreatePicture(show->dpy, show->pict_src->pixmap, format, 0, NULL);
	show->pict_dst->picture	=	XRenderCreatePicture(show->dpy, show->pict_dst->pixmap, format, CPComponentAlpha|CPRepeat, &attr);//0, NULL);
	double scale = 0.8;
	XTransform	xform = {{
		{XDoubleToFixed(1), XDoubleToFixed(0), XDoubleToFixed(0)},
		{XDoubleToFixed(0), XDoubleToFixed(1), XDoubleToFixed(0)},
		{XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(scale)}
	}};
	XRenderSetPictureTransform(show->dpy, show->pict_src->picture, &xform);
	XRenderSetPictureFilter(show->dpy, show->pict_src->picture, FilterGood, NULL, 0);
	XRenderColor color;
	color.red	=	0x35;
	color.blue	=	0x34;
	color.green	=	0x32;
	color.alpha	=	0x23;
	XRenderFillRectangle(show->dpy, PictOpSrc, show->pict_dst->picture, &color, 0, 0, width, height);

	XRenderComposite(show->dpy, PictOpOver, show->pict_src->picture, None, show->pict_dst->picture, 0, 0, 0, 0, 0, 0, width, height);
#endif

/****************************************************************************************************/

	Pixmap	pixmap			=	XCreatePixmap(show->dpy, show->win, show->width, show->height, 24);
	format					=	XRenderFindVisualFormat(show->dpy, show->visual);
	Picture picture			=	XRenderCreatePicture(show->dpy, pixmap, format, 0, NULL);
	format                  =   XRenderFindStandardFormat(show->dpy, PictStandardARGB32);
	show->pict_drawable->picture	=	XRenderCreatePicture(show->dpy, show->pict_drawable->pixmap, format, 0, NULL);

#ifdef	BLEND
	XRenderComposite(show->dpy, PictOpOver, show->pict_dst->picture, None, show->pict_drawable->picture, 0, 0, 0, 0, 0, 0,	width, height);
#endif
//	XRenderColor color;
//	color.red	=	0xbd;
//	color.blue	=	0x34;
//	color.green	=	0xbc;
//	color.alpha	=	0xff;
//	XRenderFillRectangle(show->dpy, PictOpAtop, show->pict_drawable->picture, &color, 0, 0, width, height);
	XRenderComposite(show->dpy, PictOpSrc, show->pict_drawable->picture, None, picture, 0, 0, 0, 0, 0, 0,	width, height);
	show->gc	=	XCreateGC(show->dpy, show->win, 0, NULL);

	while(1){
		XNextEvent(show->dpy, &show->event);
		switch(show->event.type){
			case Expose:
				XCopyArea(show->dpy, pixmap, show->win, show->gc, 0, 0, width, height, 0, 0);
				XFlush(show->dpy);
				break;
			case KeyPress:
			default:
				break;
		}
	}
	XCloseDisplay(show->dpy);

	return 0;
}

Pixmap bitmap_new(struct Show *show, int width, int height, char* data)
{
	int scanline;
	XImage* image;
	Pixmap bitmap;

	scanline = (width + 7) / 8; 

	bitmap = XCreatePixmap(show->dpy, show->win, width, height, 1);

	image = XCreateImage(show->dpy, show->visual, 1,
			ZPixmap, 0, (char*) data, width, height, 8, scanline);

	XPutImage(show->dpy, bitmap, show->gc, image, 0, 0, 0, 0, width, height);
	XFree(image);

	return bitmap;
} 
