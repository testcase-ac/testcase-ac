#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(1, 8);
    vector<vector<int>> tests;

    auto addValue = [](vector<int>& a, int x) {
        a.push_back(max(1, min(1000000, x)));
    };

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(0, 5);
        vector<int> a;

        if (mode == 0) {
            int n = rnd.next(1, 16);
            int hi = rnd.next(1, 40);
            for (int i = 0; i < n; ++i) {
                addValue(a, rnd.next(1, hi));
            }
        } else if (mode == 1) {
            int pairs = rnd.next(1, 8);
            for (int i = 0; i < pairs; ++i) {
                int shift = rnd.next(0, 18);
                int g = 1 << shift;
                addValue(a, 2 * g);
                addValue(a, 3 * g);
                if (rnd.next(0, 1) == 1) {
                    addValue(a, rnd.next(1, 6) * g);
                }
            }
        } else if (mode == 2) {
            int n = rnd.next(4, 20);
            int baseShift = rnd.next(0, 12);
            for (int i = 0; i < n; ++i) {
                int shift = min(19, baseShift + rnd.next(0, 7));
                addValue(a, 1 << shift);
            }
        } else if (mode == 3) {
            int distinct = rnd.next(1, 8);
            vector<int> pool;
            for (int i = 0; i < distinct; ++i) {
                pool.push_back(rnd.next(1, 1000000));
            }
            int n = rnd.next(distinct, 24);
            for (int i = 0; i < n; ++i) {
                a.push_back(rnd.any(pool));
            }
        } else if (mode == 4) {
            vector<int> pool = {1, 2, 3, 4, 7, 8, 12, 16, 31, 32, 63,
                                64, 999999, 1000000};
            int n = rnd.next(2, 18);
            for (int i = 0; i < n; ++i) {
                a.push_back(rnd.any(pool));
            }
        } else {
            int n = rnd.next(5, 25);
            int start = rnd.next(1, 999950);
            int step = rnd.next(1, 17);
            for (int i = 0; i < n; ++i) {
                addValue(a, start + i * step);
            }
        }

        shuffle(a.begin(), a.end());
        tests.push_back(a);
    }

    println((int)tests.size());
    for (const vector<int>& a : tests) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
