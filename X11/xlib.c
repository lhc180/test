#include "common.h"

//#define TDE 0
#define SHM 1
#define FUN 2
static int highbit(unsigned long ul) 

{ 
    int i;
    unsigned long hb; 
    
    hb = 0x8000; hb = (hb<<16); /* hb = 0x80000000UL */ 
    for (i=31; ((ul & hb) == 0) && i>=0; i--, ul<<=1); 
    return i; 
} 

XImage* create_ximage(Display* dpy, char* data, 
        int width, int height, int bdepth) 
{ 
    Visual          *visual = DefaultVisual(dpy, DefaultScreen(dpy)); 
    int             depth = DefaultDepth(dpy, DefaultScreen(dpy)); 
    XImage*         res; 
    int             i, j; 
    char*           idata; 
    
    res = XCreateImage(dpy, visual, depth, ZPixmap, 0 /*offset*/, 
            NULL, width, height, 32, 0); 
    if (res == NULL) { 
        return NULL; 
    } 

    idata = (char*)malloc(res->bytes_per_line*height); 
    res->data = idata; 
#if 0
    { 
        unsigned long   r, g, b, rmask, gmask, bmask, xcol; 
        int             rshift, gshift, bshift, bperpix, bperline, border; 
        char   *ip, *pp; 
        
        rmask = visual->red_mask; 
        gmask = visual->green_mask; 
        bmask = visual->blue_mask; 

        rshift = 7 - highbit(rmask); 
        gshift = 7 - highbit(gmask); 
        bshift = 7 - highbit(bmask); 

        bperline = res->bytes_per_line; 
        bperpix = res->bits_per_pixel; 
        border = res->byte_order; 

        pp = data; 

        for (i=0; i<height; i++) { 
            for (j=0; j<width; j++) { 
                b = *pp++; g = *pp++; r = *pp++; 
                pp++; 

                if (rshift<0) r = r << (-rshift); 
                else r = r >> rshift; 

                if (gshift<0) g = g << (-gshift); 
                else g = g >> gshift; 

                if (bshift<0) b = b << (-bshift); 
                else b = b >> bshift; 

                r = r & rmask; 
                g = g & gmask; 
                b = b & bmask; 

                xcol = r | g | b; 

                ip = (idata+(height-1-i)*bperline+j*bperpix/8); 
                if (bperpix == 32) { 
                    if (border == MSBFirst) { 
                        *ip++ = (xcol>>24) & 0xff; 
                        *ip++ = (xcol>>16) & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = xcol & 0xff; 
                    } 
                    else { /* LSBFirst */ 
                        *ip++ = xcol & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = (xcol>>16) & 0xff; 
                        *ip++ = (xcol>>24) & 0xff; 
                    } 
                } 
                else if (bperpix == 24) { 
                    if (border == MSBFirst) { 
                        *ip++ = (xcol>>16) & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = xcol & 0xff; 
                    } 
                    else { /* LSBFirst */ 
                        *ip++ = xcol & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = (xcol>>16) & 0xff; 
                    } 
                } 
                else if (bperpix == 16) { 
                    if (border == MSBFirst) { 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = xcol & 0xff; 
                    } 
                    else { /* LSBFirst */ 
                        *ip++ = xcol & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                    } 
                } 
                else if (bperpix == 8) { 
                    *ip++ = xcol & 0xff; 
                } 
            } 
        } 
    }
#endif
    return res; 
} 

Window create_simple_window(Display* display, int width, int height, int x, int y) 
{ 
    int     screen_num = DefaultScreen(display); 
    int     win_border_width = 2; 
    Window  win; 

    win = XCreateSimpleWindow(display, RootWindow(display, screen_num), 
            x, y, width, height, win_border_width, 
            BlackPixel(display, screen_num), 
     /*       WhitePixel(display, screen_num)*/
			0xfb
            ); 

    return win; 
} 

GC create_gc(Display* display, Window win, int reverse_video) 
{ 
    GC                  gc;	 /* handle of newly created GC. */ 
    unsigned long       valuemask = 0;	 /* which values in 'values' to */ 
    /* check when creating the GC. */ 
    XGCValues           values;	 /* initial values for the GC. */ 
    unsigned int        line_width = 2;	 /* line width for the GC. */ 
    int                 line_style = LineSolid;	 /* style for lines drawing and */ 
    int                 cap_style = CapButt;	 /* style of the line's edje and */ 
    int                 join_style = JoinBevel;	 /* joined lines.	 */ 
    int                 screen_num = DefaultScreen(display); 

    gc = XCreateGC(display, win, valuemask, &values); 
    if (gc < 0) { 
        printf("XCreateGC: \n"); 
    } 

    /* allocate foreground and background colors for this GC. */ 
    if (reverse_video) { 
        XSetForeground(display, gc, WhitePixel(display, screen_num)); 
        XSetBackground(display, gc, BlackPixel(display, screen_num)); 
    } 
    else { 
        XSetForeground(display, gc, BlackPixel(display, screen_num)); 
        XSetBackground(display, gc, WhitePixel(display, screen_num)); 
    } 

    /* define the style of lines that will be drawn using this GC. */ 
    XSetLineAttributes(display, gc, 
            line_width, line_style, cap_style, join_style); 

    /* define the fill style for the GC. to be 'solid filling'. */ 
    XSetFillStyle(display, gc, FillSolid); 

    return gc; 
} 

int place_graphics(struct Show* show)
{ 
    XPutImage(show->dpy, show->win, show->gc, show->ximage_dst, 0, 0, 0, 0, show->width, show->height); 
    return 0; 
} 
#if 0
int show_bmp_data(char* bmpdata, int bwidth, int bheight, int bdepth) 
{ 
    Display*        display;	
    int             screen_num;	
    Window          win;	
    unsigned int    display_width, display_height;	
    unsigned int    width, height;	
    char            *display_name = (char*)getenv("DISPLAY"); 
    GC              gc;	
    XImage*         img; 

    /* open connection with the X server. */ 
    display = XOpenDisplay(display_name); 
    if (display == NULL) { 
        return -1; 
    } 

    screen_num = DefaultScreen(display); 
    display_width = DisplayWidth(display, screen_num); 
    display_height = DisplayHeight(display, screen_num); 

    width   = 900; 
    height  = 700; 

    printf("window width - '%d'; height - '%d' \n", width, height); 

    win = create_simple_window(display, width, height, 0, 0); 
    gc = create_gc(display, win, 0); 
    XSelectInput(display, win, ExposureMask | KeyPressMask | 
            ButtonPressMask | StructureNotifyMask); 

    
#ifdef FUN 
    img = create_ximage(display, bmpdata, bwidth, bheight, bdepth); 
#else
#ifdef SHM
    printf("--------------------shared memmory-----------------\n");
    Visual          *visual = DefaultVisual(display, screen_num); 
    int             depth = DefaultDepth(display, screen_num); 
    int             i, j; 
    char*           idata; 
    int             shm_id;
    unsigned int    shm_virt;
    XShmSegmentInfo shminfo;
    shm_id       =       shmget(IPC_PRIVATE, 1024*1024*4, IPC_CREAT | 0777);
    if (shm_id < 0){
        printf("failed to create shared mmz memory\n");
    }else{
        printf("4M shared memory id 0x%x\n", shm_id);
    }    

    shm_virt    =       (unsigned int)shmat(shm_id, 0, 0);
    if (!shm_virt){
        printf("failed to map shared mmz memory \n");
    }

    img = XShmCreateImage(display, visual, depth,  ZPixmap, (void*)shm_virt, &shminfo, bwidth, bheight);

    shminfo.shmaddr     =       (void*)shm_virt;
    shminfo.shmid       =       shm_id;
    shminfo.readOnly    =       0;
    XShmAttach(display, &shminfo);
    XSync(display, 0);
    shmctl(shm_id, IPC_RMID, 0);
       
    idata = (char*)malloc(img->bytes_per_line*bheight); 
#else
    img = XCreateImage(display, visual, depth, ZPixmap, 0 /*offset*/, 
            NULL, bwidth, bheight, 32, 0); 
    if (img == NULL) { 
        return NULL; 
    } 

    idata = (char*)malloc(img->bytes_per_line*bheight); 
    img->data = idata; 
#endif
    do{ 
        unsigned long   r, g, b, rmask, gmask, bmask, xcol; 
        int             rshift, gshift, bshift, bperpix, bperline, border; 
         char   *ip, *pp; 
        
        rmask = visual->red_mask; 
        gmask = visual->green_mask; 
        bmask = visual->blue_mask; 

        rshift = 7 - highbit(rmask); 
        gshift = 7 - highbit(gmask); 
        bshift = 7 - highbit(bmask); 

        bperline = img->bytes_per_line; 
        bperpix = img->bits_per_pixel; 
        border = img->byte_order; 

        pp = bmpdata; 

        for (i=0; i<bheight; i++) { 
            for (j=0; j<bwidth; j++) { 
                b = *pp++; g = *pp++; r = *pp++; 
                pp++; 

                if (rshift<0) r = r << (-rshift); 
                else r = r >> rshift; 

                if (gshift<0) g = g << (-gshift); 
                else g = g >> gshift; 

                if (bshift<0) b = b << (-bshift); 
                else b = b >> bshift; 

                r = r & rmask; 
                g = g & gmask; 
                b = b & bmask; 

                xcol = r | g | b; 

                ip = (idata+(bheight-1-i)*bperline+j*bperpix/8); 
                if (bperpix == 32) { 
                    if (border == MSBFirst) { 
                        *ip++ = (xcol>>24) & 0xff; 
                        *ip++ = (xcol>>16) & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = xcol & 0xff; 
                    } 
                    else { /* LSBFirst */ 
                        *ip++ = xcol & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = (xcol>>16) & 0xff; 
                        *ip++ = (xcol>>24) & 0xff; 
                    } 
                } 
                else if (bperpix == 24) { 
                    if (border == MSBFirst) { 
                        *ip++ = (xcol>>16) & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = xcol & 0xff; 
                    } 
                    else { /* LSBFirst */ 
                        *ip++ = xcol & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = (xcol>>16) & 0xff; 
                    } 
                } 
                else if (bperpix == 16) { 
                    if (border == MSBFirst) { 
                        *ip++ = (xcol>>8) & 0xff; 
                        *ip++ = xcol & 0xff; 
                    } 
                    else { /* LSBFirst */ 
                        *ip++ = xcol & 0xff; 
                        *ip++ = (xcol>>8) & 0xff; 
                    } 
                } 
                else if (bperpix == 8) { 
                    *ip++ = xcol & 0xff; 
                } 
            } 
        } 
    }while(0);
#ifdef SHM
    memcpy((char*)shm_virt, idata, img->bytes_per_line*bheight);
#endif
#endif    
    XMapWindow(display, win); 
    XFlush(display); 
    { 
        XEvent report; 
        while (1) { 
            XNextEvent(display, &report); 
            switch (report.type) { 
            case Expose: 
                if (report.xexpose.count != 0) 
                    break; 
#ifdef FUN
                place_graphics(display, win, gc, img, width, height); 
#else
#ifdef SHM
                XShmPutImage(display, win, gc, img,  0, 0, 0, 0, bwidth, bheight, 0);
#else
                XPutImage(display, win, gc, img, 0, 0, 0, 0, bwidth, bheight); 
#endif
#endif
                break; 
            case ConfigureNotify: 
                break; 
            case ButtonPress: 
            case KeyPress: 
                break; 
            default: 
                break; 
            } /* End switch */ 
        } /* End while */ 
    } 
    return 0; 
}
#endif
