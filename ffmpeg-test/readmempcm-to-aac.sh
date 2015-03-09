#!/bin/bash
g++ readmempcm-to-aac.c -o readmempcm-to-aac -lavcodec -lavformat -lswscale -lavutil
