#include "strings.h"
#include <iostream>

static std::vector<int> buildPrefix(std::string &s) {
    int n = s.length();
    std::vector<int> p(n);
    p[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = p[i-1];
        while (j > 0 && s[i] != s[j]) {
            j = p[j-1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        p[i] = j;
    }

    return p;
}

// Assumption: text, pattern do not contain the character `$`.
std::vector<int> Strings::searchPatternKMP(std::string &text, std::string &pattern) {
    std::vector<int> res;
    std::string concat = pattern + "$" + text;
    auto lps = buildPrefix(concat);
    for (int i = pattern.size() + 1; i < concat.size(); i++) {
        if (lps[i] == pattern.size()) {
            res.push_back(i - 2 * pattern.size());
        }
    }
    return res;
}

std::vector<int> Strings::searchPatternRK(std::string& text, std::string& pattern) {
    const int p = 31;
    const int m = 1e9 + 9;

    std::vector<long long> p_pow(std::max(pattern.size(), text.size()));
    p_pow[0] = 1;
    for (int i = 1; i < p_pow.size(); i++) {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    std::vector<long long> h(text.size() + 1, 0);
    for (int i = 0; i < text.size(); i++) {
        h[i+1] = (h[i] + (text[i] + 1) * p_pow[i]) % m;
    }

    long long h_p = 0;
    for (int i = 0; i < pattern.size(); i++) {
        h_p = (h_p + (pattern[i] + 1) * p_pow[i]) % m;
    }

    std::vector<int> occurrences;
    for (int i = 0; i + pattern.size() - 1 < text.size(); i++) {
        long long cur_h = (h[i + pattern.size()] + m - h[i]) % m;
        if (cur_h == h_p * p_pow[i] % m) {
            occurrences.push_back(i);
        }
    }

    return occurrences;
}

static std::vector<int> computeZ(std::string &s) {
    int n = s.size();
    std::vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

// Assumption: text, pattern do not contain the character `$`.
std::vector<int> Strings::searchPatternZ(std::string &text, std::string &pattern) {
    std::vector<int> res;
    std::string concat = pattern + "$" + text;
    auto z = computeZ(concat);
    int m = pattern.size();
    for (int i = m + 1; i < concat.size(); ++i) {
        if (z[i] == m) {
            res.push_back(i - m - 1);
        }
    }
    return res;
}

std::vector<int> manacher_odd(std::string s) {
    int n = s.size();
    s = "$" + s + "^";
    std::vector<int> p(n + 2, 0);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = std::max(0, std::min(r - i, p[l + (r - i)]));
        
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return std::vector<int>(begin(p) + 1, end(p) - 1);
}

// Assumption: s is composed entirely of alphabetical characters.
std::vector<int> Strings::subpalindromesManacher(std::string& s) {
    std::string t;
    for (auto c : s) {
        std::string cs{c};
        t += "#" + cs;
    }
    auto res = manacher_odd(t + "#");
    return std::vector<int>(begin(res) + 1, end(res) - 1);
}

// Assumption: s is composed entirely of alphabetical characters.
std::vector<int> Strings::subpalindromesRK(std::string &s) {
    std::string t;
    for (auto c : s) {
        std::string cs{c};
        t += "#" + cs;
    }
    t += "#";

    int n = t.size();
    const long long m = 1e9 + 9;
    const long long p = 31;
    std::vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < p_pow.size(); i++) {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    std::vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++) {
        h[i+1] = (h[i] + (t[i] + 1) * p_pow[i]) % m;
    }
    std::vector<long long> hr(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        hr[i] = (hr[i + 1] + (t[i] + 1) * p_pow[n - i - 1]) % m;
    }

    std::vector<int> res(n - 2, 0);
    for (int i = 1; i < n - 1; ++i) {
        int lo = 1, hi = std::min(i, n - i - 1), best = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            long long leftHash = ((h[i] + m - h[i - mid]) % m) * p_pow[n - i] % m;
            long long rightHash = ((hr[i + 1] + m - hr[i + mid + 1]) % m) * p_pow[i + 1] % m;

            if (leftHash == rightHash) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        res[i - 1] = best + 1;
    }
    
    return res;
}
