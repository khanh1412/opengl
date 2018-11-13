#!/usr/bin/sh
g++ -g -o run main.cc sources/Engine.cc sources/Object.cc -I./include -I./include/vendor -lGL -lGLEW -lglfw ./libRenderer.so
