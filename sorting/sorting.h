#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <random>
#include <algorithm>

class Sorting {
private:
    static const int MAX_ARR_SIZE = 10'000'000;
    static const int INSERTION_SORT_THRESHOLD = 65;
    static void insertionSort(std::vector<int>& v, int start, int end);
    static void mergeSort(std::vector<int>& v, int start, int end);
    static void quickSort(std::vector<int>& v, int start, int end);
    static void hybridSort(std::vector<int>& v, int start, int end);
    static std::random_device rd;
    static std::mt19937 rng;
    
public:
    static std::vector<int> buffer;
    static void insertionSort(std::vector<int>& v);
    static void mergeSort(std::vector<int>& v);
    static void quickSort(std::vector<int>& v);
    static void hybridSort(std::vector<int>& v);
};

# endif