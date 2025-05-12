#!/bin/bash

g++ bench.cpp ../strings.cpp -o bench -O3 -march=native

# Small tests
python gen.py 100 200 400 4 8 1 26 > test.in
./bench small < test.in 2> /dev/null

# Medium tests
python gen.py 100 2000 4000 1 100 1 26 > test.in
./bench medium < test.in 2> /dev/null

# Large tests
python gen.py 100 20000 40000 1 5000 1 26 > test.in
./bench large < test.in 2> /dev/null

# Huge tests
python gen.py 100 200000 400000 1 50000 1 26 > test.in
./bench huge < test.in 2> /dev/null

python statistics.py

rm test.in bench *.times.txt