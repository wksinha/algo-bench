#!/bin/bash

rm -rf *.in *.out rktest
[ -f rktest.logs ] && cat rktest.logs >> rktest.logs.bkp && rm -f rktest.logs
g++ rktest.cpp ../strings.cpp -o rktest -O3 -march=native

for i in {1..5}; do
    python rkgen.py > "rk_test_${i}.in"
    ./rktest < rk_test_${i}.in > rk_test_${i}.out
    cat rk_test_${i}.out &>> rktest.logs
    echo "${i} tests executed"
done
cat rktest.logs

printf "\n\n\n\n\n" >> rktest.logs.bkp