#!/bin/sh

g++ -g -o server src/server.cpp -L ./lib -levent -I ./include -std=c++11
