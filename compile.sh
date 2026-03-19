#!/bin/bash

if [ $# -ne 1 ];
then
    echo "Usage: $0 <file.c>"
    echo "Enter the file name without .c extension"
    exit 1
fi

gcc "$1.c" -o "$1"

./"$1"