#include "iterative_segment_tree.h"

IterativeSegmentTree::IterativeSegmentTree(int n) {
    this->n = n;
    this->t.resize(n << 1, 0);
}

void IterativeSegmentTree::build(std::vector<int>& v) {
    this->n = v.size();
    this->t.resize(n << 1, 0);
    for (int i = 0; i < v.size(); i++) {
        t[i + n] = v[i];
    }
    for (int i = n - 1; i > 0; --i) {
        t[i] = t[i<<1] + t[i<<1|1];
    }
}

IterativeSegmentTree::IterativeSegmentTree(std::vector<int>& v) {
    build(v);
}

void IterativeSegmentTree::add(int p, int delta) {
    for (t[p += n] += delta; p > 1; p >>= 1) {
        t[p>>1] = t[p] + t[p^1];
    }
}

int IterativeSegmentTree::sum(int l, int r) {
    r++;
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
}