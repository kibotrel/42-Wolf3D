#!/bin/bash

curl http://libsdl.org/release/SDL2-2.0.9.tar.gz -o SDL_2.0.9.tar.gz
tar -xvf SDL_2.0.9.tar.gz
rm -f SDL_2.0.9.tar.gz
cd SDL2-2.0.9
./configure
make
