# Strings

## KMP
The KMP algorithm, named after Knuth, Morris, and Pratt, is an efficient implementation of the prefix function.  
Given a string *s*, of length *n*, the prefix function is defined as an array *p* of length *n*, where *p[i]* is the length of the longest proper prefix of the substring *s[0..i]* which is also a suffix of this substring.  
A proper prefix of a string is a prefix that is not equal to the string itself. By definition, *p[0] = 0*.  
Mathematically, *p[i]* = *max{k : s[0..k-1] = s[i - (k - 1)..i]}*, *k = 0..i*  
While a trivial implementation runs in *O(n<sup>2</sup>)* time, KMP runs in *O(n)* time.  

### Applications
- Search for a substring in a string
- Counting the number of occurrences of each prefix
- Compressing a string - representing a string *s* as *t+..+t* for some prefix *t* with the shortest length.

## Manacher
Manacher's algorithm provides an efficient way to find all sub-palindromes in a string *s* of length *n* in *O(n)* time.  
Formally, given a string *s* with length *n*, it finds all the pairs *(i, j)* such that substring *s[i..j]*  is a palindrome.  

### Applications
- Find largest subpalindrome
- Count no. of subpalindromes

## Rabin-Karp
Based on the idea of hashing, the Rabin-Karp algorithm compares the hash of substrings of a text *t* to that of a pattern *p*.  
The efficient implementation assumes that a matching hash implies (with high confidence) that the substring matches the pattern.  

### Applications
- Search for a substring in a string
- Counting the number of different substrings

## Z-Function
The Z-function calculates for each *i*, the greatest number of characters starting from the position *i* that coincide with the first characters of *s*.  
In other words, *z[i]* is the length of the longest string that is, at the same time, a prefix of *s* and a prefix of the suffix of *s* starting at *i*.  

### Applications
- Search for a substring in a string
- Counting the number of occurrences of each prefix
- Compressing a string - representing a string *s* as *t+..+t* for some prefix *t* with the shortest length.

## References
1. [KMP, CP-Algorithms](https://cp-algorithms.com/string/prefix-function.html)
2. [Manacher, CP-Algorithms](https://cp-algorithms.com/string/manacher.html)
3. [String-Hashing, CP-Algorithms](https://cp-algorithms.com/string/string-hashing.html)
4. [Rabin-Karp, CP-Algorithms](https://cp-algorithms.com/string/rabin-karp.html)
5. [Z-function, CP-Algorithms](https://cp-algorithms.com/string/z-function.html)