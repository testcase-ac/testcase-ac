#include "testlib.h"
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T0 = rnd.next(2, 5);
    vector<vector<pair<char,int>>> tests;
    bool hasEmpty = false, hasNonEmpty = false;

    for (int ti = 0; ti < T0; ti++) {
        int k = rnd.next(1, 20);
        vector<pair<char,int>> ops;
        vector<int> cur;
        double pIns = rnd.next(0.3, 0.7);

        for (int i = 0; i < k; i++) {
            bool doInsert = cur.empty() || rnd.next() < pIns;
            if (doInsert) {
                int n;
                if (rnd.next() < 0.1) {
                    // pick extreme
                    vector<int> ex = {INT_MIN, INT_MAX};
                    n = rnd.any(ex);
                } else {
                    n = rnd.next(-1000, 1000);
                }
                ops.emplace_back('I', n);
                cur.push_back(n);
            } else {
                // delete
                vector<int> dels = {1, -1};
                int d = rnd.any(dels);
                ops.emplace_back('D', d);
                if (!cur.empty()) {
                    // simulate removal
                    auto it = cur.begin();
                    if (d == 1) {
                        // remove one max
                        it = max_element(cur.begin(), cur.end());
                    } else {
                        // remove one min
                        it = min_element(cur.begin(), cur.end());
                    }
                    cur.erase(it);
                }
            }
        }
        if (cur.empty()) hasEmpty = true;
        else hasNonEmpty = true;
        tests.push_back(ops);
    }

    // ensure at least one empty and one non-empty result
    if (!hasEmpty) {
        vector<pair<char,int>> ops;
        ops.emplace_back('I', 5);
        ops.emplace_back('D', 1);
        ops.emplace_back('D', -1);
        tests.push_back(ops);
    }
    if (!hasNonEmpty) {
        vector<pair<char,int>> ops;
        ops.emplace_back('I', 42);
        // leave one element
        tests.push_back(ops);
    }

    int T = tests.size();
    println(T);
    for (auto &ops : tests) {
        println((int)ops.size());
        for (auto &op : ops) {
            println(op.first, op.second);
        }
    }

    return 0;
}
