#!/bin/bash
gcc -g -Wall aac_encoder.c -o aac_encoder -lfaac -lavcodec -lavformat -lavdevice -lavfilter -lavutil -lswresample -pthread  -ldl -lswscale -lasound -lz -lm
