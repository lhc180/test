#!/bin/bash
gcc -Wformat-security test.c read_bitmap.c -o test -lX11 -lXrender 
