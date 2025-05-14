#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <vector>

class SegmentTree {
private:
    int n;
    std::vector<int> t;
    
    void build(std::vector<int>& a, int v, int tl, int tr);
    int sum(int v, int tl, int tr, int l, int r);
    void add(int v, int tl, int tr, int pos, int delta);
    
public:
    SegmentTree(int n);
    SegmentTree(std::vector<int>& a);
    int sum(int l, int r);
    void add(int pos, int delta);
};

#endif