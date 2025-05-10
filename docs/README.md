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
    - Assuming program running times are random variables sampled from a distribution, the following ensues.
        - Run the program T times and note the running times, $t_1$, .., $t_n$.
        - Find the least and highest running times.  
        $lrt = \min_{1 \leq i \leq n} (t_i)$  
        $hrt = \max_{1 \leq i \leq n} (t_i)$  
        - *Claim:*  
            The median running time lies in the range [$lrt$, $hrt$] with probability $1$ - $2^{-(T - 1)}$.  
        - *Proof:*  
            Pr[$median \in [lrt, hrt]$] = $1$ - Pr[ $median < lrt$ | $hrt < median$]  
                                                        = $1$ - Pr[$median < lrt$] - Pr[$hrt < median$] (since the events are disjoint)  
                                                        = $1$ - $2^{-T}$ - $2^{-T}$  (since probability that a single execution is on either side = $2^{-1}$)  
                                                        = $1$ - $2^{-(T - 1)}$  
        - Similar arguments can be used to find $n^{th}$ percentile statistics.


## Optimizations
Unless stated otherwise, all benchmarked (C++) programs run with `Ofast`, `march=native` flags.

## References
1. [GCC Optimization Pragmas](https://nor-blog.pages.dev/posts/2021-10-26-gcc-optimization-pragmas/)