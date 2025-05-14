# Results

Each size below is tested with 10 test instances per algorithm.  
**Array lengths for test categories:**

- **Small:** 10–200
- **Medium:** 1,000–20,000
- **Large:** 100,000–2,000,000

## Sorting Results
Least and highest running times across all tests.  
|           | **insertionSort**       | **quickSort**           | **mergeSort**           | **hybridSort**          |
|-----------|-------------------------|-------------------------|-------------------------|-------------------------|
| small     | (709, 7,473)            | (768, 6,078)            |(933, 7,776)             | (763, 6,022)            |
| medium    | (141,312, 10,548,489)   | (81,225, 880,327)       |(94,431, 1,043,705)      | (72,792, 769,667)       |
| large     | (NA, NA)                | (9,733,001, 98,435,984) |(11,691,272, 120,194,603)| (8,779,871, 90,966,402) |

<p>
  <img src="sorting-stats-small.png" alt="Running Times on Small Inputs" width="500" height="300" />
  <br />
  <em>Figure 1: Least and highest execution time for sorting algorithms on small sized inputs</em>
</p>

<p>
  <img src="sorting-stats-medium.png" alt="Running Times on Medium Inputs" width="500" height="300" />
  <br />
  <em>Figure 2: Least and highest execution time for sorting algorithms on medium sized inputs</em>
</p>

<p>
  <img src="sorting-stats-large.png" alt="Running Times on Large Inputs" width="500" height="300" />
  <br />
  <em>Figure 3: Least and highest execution time for sorting algorithms on large sized inputs</em>
</p>

It is observed that for small inputs, InsertionSort is typically fast in practice, by virtue of its reliance on the same, HybridSort performs similarly, QuickSort lags behind a little and MergeSort is slightly slower still.  
In comparison, for medium to large sized inputs, InsertionSort expectedly blows up (since it is quadratic in time complexity) and HybridSort performs best, QuickSort lags behind a little and MergeSort is slightly slower still.
