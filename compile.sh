#!/bin/bash -e

./linked_lists/compile_lib.sh

gcc -O3 main.c linked_lists/lib.a -lm -lpthread -o snake