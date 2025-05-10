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
    // std::cerr << s << " " << n << " 1" << std::endl;
    std::vector<int> p(n + 2, 0);
    // std::cerr << s << " 1a" << std::endl;
    // if (true) {
        // return std::vector<int>();
    // }
    int l = 0, r = 1;
    // std::cerr << s << " 2" << std::endl;
    for(int i = 1; i <= n; i++) {
        p[i] = std::max(0, std::min(r - i, p[l + (r - i)]));
        std::cerr << i << " - " << p[i] << std::endl;
        
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    std::cerr << s << " 3" << std::endl;
    return std::vector<int>(begin(p) + 1, end(p) - 1);
}

// Assumption: s is composed entirely of alphabetical characters.
std::vector<int> Strings::subpalindromesManacher(std::string& s) {
    std::string t;
    for (auto c : s) {
        std::string cs{c};
        t += "#" + cs;
    }
    // std::cout << "M t" << t << std::endl;
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
    // std::cout << "RK t 1" << t << std::endl;

    int n = t.size();
    const long long m = 1e9 + 9;
    const long long p = 31;
    std::vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < p_pow.size(); i++) {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    std::vector<long long> h(t.size() + 1, 0);
    for (int i = 0; i < t.size(); i++) {
        h[i+1] = (h[i] + (t[i] + 1) * p_pow[i]) % m;
        // std::cout << "h[" << i + 1 << "] = " << h[i + 1] << std::endl;
        // std::cout << t[i] << " " << (t[i] + 1) << std::endl;
    }
    // std::cout << "RK t 2" << t << std::endl;
    #warning add reverse-hash for correction
    // add h_r reverse-hash

    std::vector<int> res(n - 1, 0);
    for (int i = 1; i < n; ++i) {
        int lo = 0, hi = std::min(i - 1, n - i - 1), best = 0;
        if (hi == 0) {
            continue;
        }
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int leftHash = (h[i - 1] + m - h[i - mid - 1]) % m;
            int rightHash = (h[i + mid] + m - h[i]) % m;
            if (leftHash * p_pow[mid + 1] % m == rightHash) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        res[i - 1] = best;
    }
    // std::cout << "RK t 3" << t << std::endl;
    
    return res;
}
