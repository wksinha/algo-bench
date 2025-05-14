#include "fenwick.h"

FenwickTree::FenwickTree(int n) : n(n), bit(n, 0) {}

FenwickTree::FenwickTree(std::vector<int>& a) {
    this->n = a.size();
    this->bit.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        add(i, a[i]);
    }
}

int FenwickTree::sum(int l, int r) {
    if (l > r) return 0;
    return sum(r) - (l > 0 ? sum(l - 1) : 0);
}

int FenwickTree::sum(int r) {
    int result = 0;
    for (int idx = r; idx >= 0; idx = (idx & (idx + 1)) - 1) {
        result += bit[idx];
    }
    return result;
}

void FenwickTree::add(int idx, int delta) {
    for (int i = idx; i < n; i = (i | (i + 1))) {
        bit[i] += delta;
    }
}
