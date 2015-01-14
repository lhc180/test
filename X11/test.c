#include "common.h"

#define		ROP			0
//#define		COMPOSITE	1

BOOL set_rop2(struct Show* show, int rop2)
{
	if ((rop2 < 0x01) || (rop2 > 0x10))
	{    
		printf("Unsupported ROP2: %d", rop2);
		return FALSE;
	}    

	XSetFunction(show->dpy, show->gc, rop2_table[rop2]);
	return TRUE;
}

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
	XRenderPictFormat			*format;

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
	show->ximage_dst	=	XCreateImage(show->dpy, show->visual, 32, ZPixmap, 0, data2, width2, height2, 32, 0);
	show->gc			=	XCreateGC(show->dpy, show->pict_drawable->pixmap, 0, NULL);

	show->width			=	width;
	show->height		=	height;
	XFlush(show->dpy);
	XPutImage(show->dpy, show->pict_src->pixmap, show->gc, show->ximage_src, 0, 0, 0, 0, width, height);
	XPutImage(show->dpy, show->pict_dst->pixmap, show->gc, show->ximage_dst, 0, 0, 0, 0, width2, height2);
	XPutImage(show->dpy, show->pict_drawable->pixmap, show->gc, show->ximage_dst, 0, 0, 0, 0, width2, height2);
	
	XCopyArea(show->dpy, show->pict_src->pixmap, show->pict_drawable->pixmap, show->gc, 0, 0, width, height, 0, 0);

	show->gc	=	XCreateGC(show->dpy, show->win, 0, NULL);
	while(1){
		XNextEvent(show->dpy, &show->event);
		switch(show->event.type){
			case Expose:
				XCopyArea(show->dpy, show->pict_drawable->pixmap, show->win, show->gc, 0, 0, width, height, 0, 0);
				XFlush(show->dpy);
				break;
			case KeyPress:
			default:
				break;
		}
	}
	XRenderFreePicture(show->dpy, show->pict_src->picture);
	XRenderFreePicture(show->dpy, show->pict_dst->picture);
	XRenderFreePicture(show->dpy, show->pict_drawable->picture);
	XFreePixmap(show->dpy, show->pict_src->pixmap);
	XFreePixmap(show->dpy, show->pict_dst->pixmap);
	free(buffer);
	free(buffer2);
//	free(buffer3);
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
