#include "../strings.h"
#include <iostream>
#include <chrono>
#include <fstream>

#define dbg false

using namespace std;
using namespace std::chrono;

template<typename Func>
void benchmarkAndLog(const string& methodName, const string& testType, Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();

    auto ns = duration_cast<nanoseconds>(end - start).count();

    ofstream out(methodName + "." + testType + ".times.txt", ios::app);
    out << ns << '\n';
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <test-type>\n";
        return 1;
    }

    string testType = argv[1];

    int tests;
    cin >> tests;

    for (int t = 0; t < tests; t++) {
        string text, pattern;
        cin >> text >> pattern;

        // PATTERN MATCHING
        benchmarkAndLog("searchPatternRK", testType, [&]() {
            vector<int> matchesRK = Strings::searchPatternRK(text, pattern);
            cerr << matchesRK.size() << std::endl;
        });

        benchmarkAndLog("searchPatternKMP", testType, [&]() {
            vector<int> matchesKMP = Strings::searchPatternKMP(text, pattern);
            cerr << matchesKMP.size() << std::endl;
        });

        benchmarkAndLog("searchPatternZ", testType, [&]() {
            vector<int> matchesZ = Strings::searchPatternZ(text, pattern);
            cerr << matchesZ.size() << std::endl;
        });

        // PALINDROMES
        benchmarkAndLog("subpalindromesRK", testType, [&]() {
            vector<int> palindromesRK = Strings::subpalindromesRK(text);
            cerr << palindromesRK.size() << std::endl;
        });

        benchmarkAndLog("subpalindromesManacher", testType, [&]() {
            vector<int> palindromesManacher = Strings::subpalindromesManacher(text);
            cerr << palindromesManacher.size() << std::endl;
        });
    }

    return 0;
}
