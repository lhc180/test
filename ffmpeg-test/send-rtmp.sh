#!/bin/bash
g++ send-rtmp.c -o send-rtmp -lavcodec -lavformat -lswscale -lavutil
