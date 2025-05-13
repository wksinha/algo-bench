#include "sorting.h"

std::vector<int> Sorting::buffer(Sorting::MAX_ARR_SIZE);
std::random_device Sorting::rd;
std::mt19937 Sorting::rng(rd());

void Sorting::insertionSort(std::vector<int>& v, int start, int end) {
    for (int i, k = start; ++k <= end; ) {
        long vi = v[i = k];

        if (vi < v[i - 1]) {
            while (--i >= start && vi < v[i]) {
                v[i + 1] = v[i];
            }
            v[i + 1] = vi;
        }
    }
}

void Sorting::insertionSort(std::vector<int>& v) {
    Sorting::insertionSort(v, 0, v.size() - 1);
}

void Sorting::mergeSort(std::vector<int>& v, int start, int end) {
    if (end <= start) {
        return;
    }

    int mid = (start + end) >> 1;
    mergeSort(v, start, mid);
    mergeSort(v, mid + 1, end);

    int l = start;
    int r = mid + 1;
    int pos = l;
    while (l <= mid && r <= end) {
        if (v[l] <= v[r]) {
            Sorting::buffer[pos++] = v[l++];
        } else {
            Sorting::buffer[pos++] = v[r++];
        }
    }

    while (l <= mid) {
        Sorting::buffer[pos++] = v[l++];
    }

    while (r <= end) {
        Sorting::buffer[pos++] = v[r++];
    }

    std::copy(Sorting::buffer.begin() + start, Sorting::buffer.begin() + end + 1, v.begin() + start);
}

void Sorting::mergeSort(std::vector<int>& v) {
    Sorting::mergeSort(v, 0, v.size() - 1);
}

void Sorting::quickSort(std::vector<int>& v, int start, int end) {
    if (start >= end) {
        return;
    }

    std::uniform_int_distribution<int> dist(start, end);
    int pivotIndex = dist(Sorting::rng);
    int pivot = v[pivotIndex];

    std::swap(v[pivotIndex], v[end]);

    int i = start;
    for (int j = start; j < end; ++j) {
        if (v[j] < pivot) {
            std::swap(v[i], v[j]);
            ++i;
        }
    }
    std::swap(v[i], v[end]);

    Sorting::quickSort(v, start, i - 1);
    Sorting::quickSort(v, i + 1, end);
}

void Sorting::quickSort(std::vector<int>& v) {
    Sorting::quickSort(v, 0, v.size() - 1);
}

void Sorting::hybridSort(std::vector<int>& v, int start, int end) {
    if (start >= end) {
        return;
    }

    if (end - start + 1 <= Sorting::INSERTION_SORT_THRESHOLD) {
        Sorting::insertionSort(v, start, end);
    } else {
        std::uniform_int_distribution<int> dist(start, end);
        int pivotIndex = dist(Sorting::rng);
        int pivot = v[pivotIndex];
    
        std::swap(v[pivotIndex], v[end]);
    
        int i = start;
        for (int j = start; j < end; ++j) {
            if (v[j] < pivot) {
                std::swap(v[i], v[j]);
                ++i;
            }
        }
        std::swap(v[i], v[end]);
    
        Sorting::hybridSort(v, start, i - 1);
        Sorting::hybridSort(v, i + 1, end);
    
    }
}

void Sorting::hybridSort(std::vector<int>& v) {
    Sorting::hybridSort(v, 0, v.size() - 1);
}