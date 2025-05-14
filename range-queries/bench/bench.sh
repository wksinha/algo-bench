#!/bin/bash

g++ bench.cpp ../fenwick.cpp ../iterative_segment_tree.cpp ../segment_tree.cpp -o bench -O3 -march=native

# Small-1
python gen.py 10 10 100 10 100 > test.in
./bench small-1 < test.in 2> /dev/null

# Small-2
python gen.py 10 10 100 100 1000 > test.in
./bench small-2 < test.in 2> /dev/null

# Medium-1
python gen.py 10 1000 10000 1000 10000 > test.in
./bench medium-1 < test.in 2> /dev/null

# Medium-2
python gen.py 10 1000 10000 10000 100000 > test.in
./bench medium-2 < test.in 2> /dev/null

# Large
python gen.py 10 100000 1000000 100000 1000000 > test.in
./bench large < test.in 2> /dev/null

python statistics.py

rm test.in bench *.times.txt