#!/bin/bash

CMD="gcc -o main main.cpp tcp.cpp /usr/local/lib/libuv.a -framework CoreFoundation -framework CoreServices -lstdc++";
echo $CMD;
$CMD;

./main
