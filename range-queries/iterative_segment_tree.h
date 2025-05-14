#ifndef ITERATIVE_SEGTREE_H
#define ITERATIVE_SEGTREE_H

#include <vector>

class IterativeSegmentTree {
private:
    int n;
    std::vector<int> t;
    void build(std::vector<int>& v);
public:
    IterativeSegmentTree(int n);
    IterativeSegmentTree(std::vector<int>& v);
    void add(int p, int delta);
    int sum(int l, int r);
};

#endif