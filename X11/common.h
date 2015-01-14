#ifndef		_COMMON_H_
#define		_COMMON_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#define		TRUE	0
#define		FALSE	1
#define		WIDTH	900
#define		HEIGHT	700

typedef	int BOOL;

struct Show{
	Display		*dpy;
	Window		win;
	int			screen;
	GC			gc;
	Visual		*visual;
	XVisualInfo vinfo;
	XSetWindowAttributes attr;
	
	XImage		*ximage_src;
	XImage		*ximage_dst;
	uint32_t	width;
	uint32_t	height;

	struct PictInfo	*pict_src;
	struct PictInfo	*pict_dst;
	struct PictInfo	*pict_drawable;

	XEvent		event;
};

struct PictInfo{
	Pixmap		pixmap;
	Picture		picture;
	XRenderPictureAttributes	*attr;
};

static const char rop2_table[] =
{
	0,   
	GXclear,        /* 0 */
	GXnor,          /* DPon */
	GXandInverted,  /* DPna */
	GXcopyInverted, /* Pn */
	GXandReverse,   /* PDna */
	GXinvert,       /* Dn */
	GXxor,          /* DPx */
	GXnand,         /* DPan */
	GXand,          /* DPa */
	GXequiv,        /* DPxn */
	GXnoop,         /* D */
	GXorInverted,   /* DPno */
	GXcopy,         /* P */
	GXorReverse,    /* PDno */
	GXor,           /* DPo */
	GXset           /* 1 */
};

void ReadPic(char* file, uint8_t *rgb, int32_t *pwidth, int32_t *pheight);
int read_bmp_file(char* filename, char * const buffer, char** data, int* width, int* height, int* depth);
inline void RGB2ARGB(uint8_t *src, uint8_t *dest, int32_t width, int32_t height);

XImage* create_ximage(Display* dpy, char* data, int width, int height, int bdepth);
Window create_simple_window(Display* display, int width, int height, int x, int y);
GC create_gc(Display* display, Window win, int reverse_video);
int place_graphics(struct Show *show);

#endif
