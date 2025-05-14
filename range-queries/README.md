# Range-Queries

## Fenwick Trees (Binary Indexed Trees)
A Fenwick tree is an implicit tree where nodes are consecutively numbered, and parent-child relationships are determined by arithmetic on the node indexes.  
An important function in this index arithmetic is the least significant set bit. This is the greatest power of two which divides an index i {\displaystyle i}. This is the power of two (1, 2, 4, 8, ...) and not the exponent (0, 1, 2, 3, ...). It can be efficiently computed in two's complement arithmetic.  
- Precompute: $O(n)$ for an $n$ length array.
- Query: $O(log(n))$

## Segment Trees
A Segment Tree is a data structure that stores information about array intervals as a tree. This allows answering range queries over an array efficiently, while still being flexible enough to allow quick modification of the array.  
We explore one bottom-up and one top-down implementation.
- Precompute: $O(n)$ for an $n$ length array.
- Query: $O(log(n))$

## Results
Refer [benchmarks](bench/README.md)

## References
1. [Fenwick Tree, CP-Algorithms](https://cp-algorithms.com/data_structures/fenwick.html)
2. [Segment Tree, CP-Algorithms](https://cp-algorithms.com/data_structures/segment_tree.html)
3. [Iterative Segment Tree, Codeforces](https://codeforces.com/blog/entry/18051)
