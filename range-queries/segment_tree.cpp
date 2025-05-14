#include "segment_tree.h"
#include <algorithm>

SegmentTree::SegmentTree(int n) {
    this->n = n;
    this->t.resize(n << 2, 0);
}

void SegmentTree::build(std::vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}

SegmentTree::SegmentTree(std::vector<int>& a) {
    this->n = a.size();
    this->t.resize(n << 2, 0);
    build(a, 1, 0, a.size() - 1);
}

int SegmentTree::sum(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, std::min(r, tm))
           + sum(v*2+1, tm+1, tr, std::max(l, tm+1), r);
}

int SegmentTree::sum(int l, int r) {
    return sum(1, 0, n - 1, l, r);
}

void SegmentTree::add(int v, int tl, int tr, int pos, int delta) {
    if (tl == tr) {
        t[v] += delta;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            add(v*2, tl, tm, pos, delta);
        else
            add(v*2+1, tm+1, tr, pos, delta);
        t[v] = t[v*2] + t[v*2+1];
    }
}

void SegmentTree::add(int pos, int delta) {
    add(1, 0, n - 1, pos, delta);
}