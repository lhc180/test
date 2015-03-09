#!/bin/bash
g++ pcm-to-aac.c -o pcm-to-aac -lavcodec -lavformat -lswscale -lavutil
