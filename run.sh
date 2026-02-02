#!/bin/bash

mkdir -p bin && g++ -o ./bin/main -fopenmp ./src/main.cpp && ./bin/main
