#!/bin/bash -e

cd $(dirname $(readlink -f $0))
gcc *.c -c
ar rcs lib.a *.o