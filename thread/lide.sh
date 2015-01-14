#!/bin/bash/
gcc Queue.c test.c -o test `pkg-config --cflags gtk+-2.0` `pkg-config --libs glib-2.0 gthread-2.0`
