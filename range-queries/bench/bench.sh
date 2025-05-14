#!/bin/bash

g++ bench.cpp ../sorting.cpp -o bench -O3 -march=native

# Small tests
python gen.py 10 10 200 1 32000 > test.in
./bench small < test.in 2> /dev/null

# Medium tests
python gen.py 10 1000 20000 1 1000000 > test.in
./bench medium < test.in 2> /dev/null

# Large tests
python gen.py 10 100000 2000000 1 1000000000 > test.in
./bench large < test.in 2> /dev/null

python statistics.py

rm test.in bench *.times.txt