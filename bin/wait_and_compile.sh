#!/bin/bash

[[ $# == 0 ]] && echo "Usage: $0 <file to watch>" && exit -1

readonly source_file=$1
echo Wait for $source_file

base=${source_file%.*}
cc=clang++-4.0

echo Using standard ${std:-c++14}

while :; do

  inotifywait -qe modify $base.cpp -qe modify *.h
  clear

  $cc -Wall -g -std=${std:-c++1y} -o tmp/$base.o $base.cpp && tmp/$base.o
done
