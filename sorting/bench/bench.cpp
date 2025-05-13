#include "../sorting.h"
#include <string>
#include <functional>
#include <iostream>
#include <chrono>
#include <fstream>

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
        std::vector<int> vec;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int vi;
            cin >> vi;
            vec.push_back(vi);
        }

        std::vector<int> v1(vec.begin(), vec.end());
        std::vector<int> v2(vec.begin(), vec.end());
        std::vector<int> v3(vec.begin(), vec.end());
        std::vector<int> v4(vec.begin(), vec.end());

        if (n <= 20'000) {
            benchmarkAndLog("insertionSort", testType, [&]() {
                Sorting::insertionSort(v1);
            });
        }
        
        benchmarkAndLog("quickSort", testType, [&]() {
            Sorting::quickSort(v2);
        });

        benchmarkAndLog("mergeSort", testType, [&]() {
            Sorting::mergeSort(v3);
        });

        benchmarkAndLog("hybridSort", testType, [&]() {
            Sorting::hybridSort(v4);
        });
    }

    return 0;
}