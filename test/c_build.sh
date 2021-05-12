#!/bin/sh

g++ -g -o client src/client.cpp -L ./lib -levent -I ./include -std=c++11
