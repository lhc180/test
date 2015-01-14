#ifndef __TEST_COMMON_H
#define __TEST_COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <X11/keysym.h>

void ReadPic(char* file, uint8_t *rgb, int32_t *pwidth, int32_t *pheight);
int read_bmp_file(char* filename, char * const buffer, 
                char** data, int* width, int* height, int* depth);
inline void RGB2ARGB(uint8_t *src, uint8_t *dest, int32_t width, int32_t height);

XImage* create_ximage(Display* dpy, char* data, 
                int width, int height, int bdepth);
Window create_simple_window(Display* display, int width, int height, int x, int y);
GC create_gc(Display* display, Window win, int reverse_video);
int place_graphics(Display* display, Window win, GC gc, XImage* img, 
                unsigned int width, unsigned int height);
int show_bmp_data(char* bmpdata, int bwidth, int bheight, int bdepth);

#endif
