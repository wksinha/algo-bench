# Algo-Bench

## Analysis
Algorithms' algorithmic complexity analysis and correctness guarantees where relevant are included.

## Benchmarking
Real world performance of algorithms/programs depends on a variety of factors such as inputs, infrastructure capabilities, environment, program optimizations, etc.  
Theoretically optimal algorithms aren't necessarily the best solutions in practice. To understand and study these differences, we benchmark programs as follows:  
- Program running times may vary, and are considered to be random variables.
    - We would like to find statistical guarantees about the expected running times.
    - Since expectation and variance are unknown, concentration inequalities cannot be used to estimate tight bounds on expectation.
    - Considering the above, we instead study the n-th percentile performance with strict statistical guarantees.
- Benchmarking Pipeline:
    1. Generate diffrent sized inputs.
    2. Repeatedly run programs over the above inputs.
    3. Gather and compile running time statistics.

## Optimizations
Unless stated otherwise, all benchmarked (C++) programs run with `Ofast`, `march=native` flags.

## References
1. [GCC Optimization Pragmas](https://nor-blog.pages.dev/posts/2021-10-26-gcc-optimization-pragmas/)