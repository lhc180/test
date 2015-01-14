#!/bin/bash
gcc -Wformat-security rop.c read_bitmap.c -o rop -lX11 -lXrender 
