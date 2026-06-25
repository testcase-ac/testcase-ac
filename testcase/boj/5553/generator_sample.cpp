#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampValue(int x) {
    return max(1, min(100000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    if (mode == 5) n = rnd.next(31, 80);

    vector<pair<int, int>> bugs;

    if (mode == 0) {
        int base = rnd.next(1, 20);
        int span = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) {
            int a = clampValue(base + rnd.next(-span, span));
            int b = clampValue(a + rnd.next(0, 20));
            bugs.emplace_back(a, b);
        }
    } else if (mode == 1) {
        int limit = rnd.any(vector<int>{1, 2, 10, 99990, 100000});
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 100000);
            int b = rnd.next(1, limit);
            bugs.emplace_back(a, b);
        }
    } else if (mode == 2) {
        int threshold = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            int a = clampValue(threshold + rnd.next(-200, 200));
            int b = threshold;
            bugs.emplace_back(a, b);
        }
    } else if (mode == 3) {
        int low = rnd.next(1, 50);
        int high = rnd.next(99950, 100000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                bugs.emplace_back(rnd.next(1, low), rnd.next(high, 100000));
            } else if (rnd.next(0, 1) == 0) {
                bugs.emplace_back(rnd.next(high, 100000), rnd.next(1, low));
            } else {
                bugs.emplace_back(rnd.next(low, high), rnd.next(low, high));
            }
        }
    } else if (mode == 4) {
        int avg = rnd.next(2, 99999);
        for (int i = 0; i < n; ++i) {
            int a = clampValue(avg + rnd.next(-50, 50));
            int b = clampValue(avg + rnd.next(-10, 10));
            bugs.emplace_back(a, b);
        }
    } else {
        int groups = rnd.next(2, 6);
        vector<pair<int, int>> patterns;
        for (int i = 0; i < groups; ++i) {
            int a = rnd.next(1, 100000);
            int b = rnd.next(1, 100000);
            patterns.emplace_back(a, b);
        }
        for (int i = 0; i < n; ++i) {
            auto p = rnd.any(patterns);
            bugs.emplace_back(clampValue(p.first + rnd.next(-3, 3)),
                              clampValue(p.second + rnd.next(-3, 3)));
        }
    }

    shuffle(bugs.begin(), bugs.end());

    println(n);
    for (auto [a, b] : bugs) {
        println(a, b);
    }

    return 0;
}
