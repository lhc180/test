#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#define NegMod(x, y) ((y) - (((-x)-1) % (7)) - 1)
#define NUMPOINTS 100
#define WIDTH         600   /* Size of large window to work within  */
#define HEIGHT        600

InitBltLines(XPoint *points)
{
    int i, x, y;

    points[0].x = points[0].y = y = 0;

    for (i = 1; i != NUMPOINTS/2; i++) {
        if (i & 1) {
            points[i].x = WIDTH-1;
        } else {
            points[i].x = 0;
        }
        y += HEIGHT / (NUMPOINTS/2);
        points[i].y = y;
    }

    x = 0;
    for (i = NUMPOINTS/2; i!= NUMPOINTS; i++) {
        if (i & 1) {
            points[i].y = HEIGHT-1;
        } else {
            points[i].y = 0;
        }
        x += WIDTH / (NUMPOINTS/2);
        points[i].x = x;
    }
}

void
InitScroll(Display *d, Window w, GC fggc, XPoint *points)
{
    InitBltLines(points);
    XDrawLines(d, w, fggc, points, NUMPOINTS, CoordModeOrigin);
}

static void
InitCopyLocations(XSegment **segsap, XSegment **segsbp, int size, int reps)
{
    int x1, y1, x2, y2, i;
    int xinc, yinc;
    int width, height;
    XSegment *segsa, *segsb;

    /* Try to exercise all alignments of src and destination equally, as well
       as all 4 top-to-bottom/bottom-to-top, left-to-right, right-to-left
       copying directions.  Computation done here just to make sure slow
       machines aren't measuring anything but the XCopyArea calls.
    */
    xinc = (size & ~3) + 1;
    yinc = xinc + 3;

    width = (WIDTH - size) & ~31;
    height = (HEIGHT - size) & ~31;

    x1 = 0;
    y1 = 0;
    x2 = width;
    y2 = height;

    segsa = (XSegment *)malloc(reps * sizeof(XSegment));
    segsb = (XSegment *)malloc(reps * sizeof(XSegment));

    for (i = 0; i != reps; i++) {
        segsa[i].x1 = x1;
        segsa[i].y1 = y1;
        segsa[i].x2 = x2;
        segsa[i].y2 = y2;

        /* Move x2, y2, location backward */
        x2 -= xinc;
        if (x2 < 0) {
            x2 = NegMod(x2, width);
            y2 -= yinc;
            if (y2 < 0) {
                y2 = NegMod(y2, height);
            }
        }

        segsb[i].x1 = x1;
        segsb[i].y1 = y1;
        segsb[i].x2 = x2;
        segsb[i].y2 = y2;

        /* Move x1, y1 location forward */
        x1 += xinc;
        if (x1 > width) {
            x1 %= 32;
            y1 += yinc;
            if (y1 > height) {
                y1 %= 32;
            }
        }
    } /* end for */

    *segsap = segsa;
    *segsbp = segsb;
}

void
InitCompositeWin(Display     *d,
                 Window       w, 
                 XVisualInfo *vinfo,
                 GC           fggc,
                 int          size, 
                 int          reps,
                 XPoint      *points,
                 Picture     *winPict,
                 XSegment   **segsap,
                 XSegment   **segsbp)
{
    XRenderPictFormat   *format;

    InitScroll(d, w, fggc, points);
    InitCopyLocations(segsap, segsbp, size, reps);
    format = XRenderFindVisualFormat(d, vinfo->visual);
    *winPict = XRenderCreatePicture(d, w, format, 0, NULL);
}

static void 
Compwinwin(Display  *d,
           int       size,
           int       reps,
           Picture   winPict,
           XSegment *segsa,
           XSegment *segsb)
{
    XSegment *sa, *sb;
    Picture src, dst;
    int i;

    src = dst = winPict;
    for (sa = segsa, sb = segsb, i = 0; i != reps; i++, sa++, sb++) {
        XRenderComposite(d, PictOpOver,
                  src, None, dst,
                  sa->x1, sa->y1, 0, 0, 
                  sa->x2, sa->y2, size, size);
        XRenderComposite(d, PictOpOver,
                  src, None, dst,
                  sa->x2, sa->y2, 0, 0, sa->x1, sa->y1, size, size);
        XRenderComposite(d, PictOpOver,
                  src, None, dst,
                  sb->x2, sb->y2, 0, 0, sb->x1, sb->y1, size, size);
        XRenderComposite(d, PictOpOver,
                  src, None, dst,
                  sb->x1, sb->y1, 0, 0, sb->x2, sb->y2, size, size);
    }
}

static void
MidScroll(Display *d, Window w, GC fggc, XPoint *points)
{
    XClearWindow(d, w);
    XDrawLines(d, w, fggc, points, NUMPOINTS, CoordModeOrigin);
}

static void 
ProcessTest(Display      *d,
            int           screen,
            Window        w,
            XVisualInfo  *vinfo, 
            unsigned long fg,
            unsigned long bg)
{
#define WIN_SIZE 500
#define REPS     200

    XGCValues gcvfg;
    XPoint points[NUMPOINTS];
    GC fggc;
    Picture winPict;
    XSegment *segsa, *segsb;

    gcvfg.graphics_exposures = False;
    gcvfg.plane_mask = ~0L;
    gcvfg.function = GXcopy;
    gcvfg.foreground = fg;
    gcvfg.background = bg;

    int i, repeat = 10;

    fggc = XCreateGC(d, w, GCForeground | GCBackground | GCGraphicsExposures
                         | GCFunction | GCPlaneMask, &gcvfg);

    InitCompositeWin(d, w, vinfo, fggc, WIN_SIZE, REPS,
                     points, &winPict, &segsa, &segsb); 

    for (i = 0; i != repeat; i++) {
        printf("%d Testing...\n", i);
        Compwinwin(d, WIN_SIZE, REPS,
                   winPict, segsa, segsb);
        MidScroll(d, w, fggc, points) ;
    }
}

int main ()
{
	const char *display_name = NULL;
    Display *d;
	int screen; 

    unsigned long vmask;
    XVisualInfo *vinfolist, vinfotempl;
    Colormap cmap;
    int n;

    unsigned long bg, fg;


    XSetWindowAttributes xswa;
    Window w;

	d = XOpenDisplay(display_name);
	assert (d);
	screen = DefaultScreen(d);

    vmask = VisualIDMask | VisualScreenMask;
    vinfotempl.visualid = XVisualIDFromVisual(XDefaultVisual(d, screen));
    vinfotempl.screen = screen;
    vinfolist = XGetVisualInfo(d, vmask, &vinfotempl, &n);
	printf("XVisualInfo.depth: %d\n", vinfolist->depth);
    if (!vinfolist || n != 1) {
        fprintf (stderr, "can't get visual info of default visual\n");
        exit(1);
    }
    cmap = XDefaultColormap(d, screen);

    fg = BlackPixel(d, screen);
    bg = WhitePixel(d, screen);

    xswa.background_pixel = bg;
    xswa.border_pixel = fg;
    xswa.colormap = cmap;
    xswa.override_redirect = True;
    xswa.backing_store = NotUseful;
    xswa.save_under = False;

    w = XCreateWindow(d, DefaultRootWindow(d), 0, 0, 600, 600, 1,
        vinfolist->depth, CopyFromParent, vinfolist->visual,
        CWBackPixel | CWBorderPixel | CWColormap | CWOverrideRedirect
        | CWBackingStore | CWSaveUnder, &xswa);
    XMapWindow (d, w);

    ProcessTest(d, screen, w, vinfolist, fg, bg);

    return 0;
}
