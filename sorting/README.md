# Sorting

## Insertion Sort
Standard insertion sort with $O(n^2)$ running time for an $n$ length array.
```pseudocode
i ← 1
while i < length(A)
    j ← i
    while j > 0 and A[j-1] > A[j]
        swap A[j] and A[j-1]
        j ← j - 1
    end while
    i ← i + 1
end while
```

## Merge Sort
Standard merge sort with $O(n*log(n))$ running time for an $n$ length array.
```pseudocode
algorithm merge_sort(list m) is
    if length of m ≤ 1 then
        return m

    var left := empty list
    var right := empty list
    for each x with index i in m do
        if i < (length of m)/2 then
            add x to left
        else
            add x to right

    left := merge_sort(left)
    right := merge_sort(right)

    return merge(left, right)
```

```pseudocode
algorithm merge(left, right) is
    var result := empty list

    while left is not empty and right is not empty do
        if first(left) ≤ first(right) then
            append first(left) to result
            left := rest(left)
        else
            append first(right) to result
            right := rest(right)

    while left is not empty do
        append first(left) to result
        left := rest(left)

    while right is not empty do
        append first(right) to result
        right := rest(right)

    return result
```

## QuickSort
Standard quick sort using random-pivot with worst case $O(n^2)$ and average case $O(n*log(n))$ running time for an $n$ length array.
```pseudocode
algorithm quicksort(A, lo, hi) is 
  if lo >= hi || lo < 0 then 
    return

  p := partition(A, lo, hi) 

  quicksort(A, lo, p - 1)
  quicksort(A, p + 1, hi)
```

```pseudocode
algorithm partition(A, lo, hi) is 
  pivot_idx = random(lo, hi)
  swap A[pivot_idx] and A[hi]
  pivot := A[hi]
  i := lo

  for j := lo to hi - 1 do 
    if A[j] <= pivot then 
      swap A[i] with A[j]
      i := i + 1

  swap A[i] with A[hi]
  return i
```

## Hybrid Sort
While a variety of hybrid sorting algorithms exist, we study a mix of quicksort and insertion sort for its practical efficiency.  
A mix of the quick-sort above and insertion sort, with $INSERTION\_SORT\_THRESHOLD = 65$.  
A subarray $s$ of length $slen$ is sorted using insertion sort if $slen \leq INSERTION\_SORT\_THRESHOLD$.  
Otherwise, the mechanics of quick sort as above are applied.  
Algorithm runs with worst case $O(n^2)$ and average case $O(n*log(n))$ running time for an $n$ length array.  
Faster in practice considering the practical improvements through insertion sort's efficiency over small subarrays.  
Other noteworthy hybrids:
- MergeSort + Insertion Sort  
Same as above, applying insertion sort on small subarrays.  
An interesting variant of the same can be found under [Timsort](https://en.wikipedia.org/wiki/Timsort).  
- QuickSort + HeapSort  
This algorithm applies quicksort till a recursive-depth of $O(log(n))$ for an $n$ length array, and switches to heapsort thereafter if still unsorted.  
Doing so allows the algorithm to guarantee worst case $O(n*log(n))$ running time while benefitting from general efficiency of quicksort.

## Results
Refer [benchmarks](bench/README.md)

## References
1. [Insertion Sort, Wikipedia](https://en.wikipedia.org/wiki/Insertion_sort)
2. [Merge Sort, Wikipedia](https://en.wikipedia.org/wiki/Merge_sort)
3. [QuickSort, Wikipedia](https://en.wikipedia.org/wiki/Quicksort)
4. [Dual Pivot Quicksort, JDK](https://github.com/openjdk/jdk/blob/master/src/java.base/share/classes/java/util/DualPivotQuicksort.java)
5. [Dual Pivot Quicksort, Stack-Overlfow](https://stackoverflow.com/questions/20917617/whats-the-difference-of-dual-pivot-quick-sort-and-quick-sort)