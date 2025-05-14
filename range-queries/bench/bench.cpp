#include "../fenwick.h"
#include "../segment_tree.h"
#include "../iterative_segment_tree.h"
#include <string>
#include <vector>
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
        vector<int> vec;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int vi;
            cin >> vi;
            vec.push_back(vi);
        }
        int queryCount;
        cin >> queryCount;
        vector<tuple<int, int, int>> queries;
        for (int q = 0; q < queryCount; q++) {
            tuple<int, int, int> query;
            int type, v1, v2;
            cin >> type >> v1 >> v2;
            queries.push_back(make_tuple(type, v1, v2));
        }

        benchmarkAndLog("fenwickTree", testType, [&]() {
            FenwickTree bit(vec);
            for (auto query : queries) {
                int type = get<0>(query);
                int v1 = get<1>(query);
                int v2 = get<2>(query);
                if (type) {
                    bit.sum(v1, v2);
                } else {
                    bit.add(v1, v2);
                }
            }
        });

        benchmarkAndLog("segmentTree", testType, [&]() {
            SegmentTree st(vec);
            for (auto query : queries) {
                int type = get<0>(query);
                int v1 = get<1>(query);
                int v2 = get<2>(query);
                if (type) {
                    st.sum(v1, v2);
                } else {
                    st.add(v1, v2);
                }
            }
        });

        benchmarkAndLog("iterativeSegmentTree", testType, [&]() {
            IterativeSegmentTree st(vec);
            for (auto query : queries) {
                int type = get<0>(query);
                int v1 = get<1>(query);
                int v2 = get<2>(query);
                if (type) {
                    st.sum(v1, v2);
                } else {
                    st.add(v1, v2);
                }
            }
        });
    }

    return 0;
}