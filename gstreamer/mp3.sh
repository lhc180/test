#!/bin/sh
gcc mp3.c -o mp3 `pkg-config gstreamer-0.10 glib-2.0 gtk+-2.0 --cflags --libs`
#-I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include/ -I/usr/include/libxml2 -lgstreamer-0.10
