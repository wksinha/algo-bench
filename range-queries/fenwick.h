#ifndef FENWICK_H
#define FENWICK_H

#include <vector>

class FenwickTree {
private:
    int n;
    std::vector<int> bit;
    int sum(int r);

public:
    FenwickTree(int n);
    FenwickTree(std::vector<int>& a);
    int sum(int l, int r);
    void add(int idx, int delta);
};


#endif