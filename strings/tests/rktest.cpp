#include "../strings.h"
#include <iostream>
#include <unordered_set>

#define dbg false

int main() {
    int tests;
    std::cin >> tests;
    
    for (int t = 0; t < tests; t++) {
        std::string text;
        std::string pattern;
        std::cin >> text >> pattern;

        // PATTERN MATCHING
        std::vector<int> matchesRK = Strings::searchPatternRK(text, pattern);
        std::vector<int> matchesKMP = Strings::searchPatternKMP(text, pattern);
        std::vector<int> matchesZ = Strings::searchPatternZ(text, pattern);

        if (matchesKMP != matchesZ) {
            std::cerr << "Matches failed for KMP, Z-Function on test: " << t << std::endl;
            return 1;
        }

        std::unordered_set<int> rk(matchesRK.begin(), matchesRK.end());
        std::unordered_set<int> kmp(matchesKMP.begin(), matchesKMP.end());
        for (int match : kmp) {
            if (!rk.count(match)) {
                std::cerr << "Mismatch between KMP and Rabin-Karp, match from KMP not found in Rabin-Karp on test" << t << std::endl;
                return 1;
            }
        }

        int extraMatches = matchesRK.size() - matchesKMP.size();
        if (extraMatches > 0) {
            std::cout << extraMatches << " extra matches with Rabin-Karp on test: " << t << std::endl;
        }

        // PALINDROMES
        std::vector<int> palindromesRK = Strings::subpalindromesRK(text);
        std::vector<int> palindromesManacher = Strings::subpalindromesManacher(text);

        if (palindromesRK.size() != palindromesManacher.size()) {
            std::cerr << "Invalid result size for palindrome matches on test" << t << std::endl;
            return 1;
        }
        int differences = 0;
        for (int i = 0; i < palindromesRK.size(); i++) {
            if (palindromesRK[i] > palindromesManacher[i]) {
                differences++;
            } else if (palindromesRK[i] < palindromesManacher[i]) {
                if (dbg) {
                    for (size_t i = 0; i < palindromesRK.size(); ++i) {
                        std::cout << "rk[" << i << "] = " << palindromesRK[i] << std::endl;
                    }
                    for (size_t i = 0; i < palindromesManacher.size(); ++i) {
                        std::cout << "m[" << i << "] = " << palindromesManacher[i] << std::endl;
                    }
                }
                
                std::cerr << "Invalid result. Rabin-Karp under-counting against Manacher on test" << t << std::endl;
                return 1;
            }
        }
    }

    return 0;
}