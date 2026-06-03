#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int clampValue(long long x) {
    return (int)max(1LL, min(1000000000LL, x));
}

void addCase(vector<pair<int, int>>& cases, long long n, long long m) {
    cases.push_back({clampValue(n), clampValue(m)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int mode = rnd.next(6);

    if (mode == 0) {
        int t = rnd.next(6, 25);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 12);
            int m = rnd.next(1, 12);
            addCase(cases, n, m);
        }
    } else if (mode == 1) {
        int t = rnd.next(5, 18);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 1000000);
            addCase(cases, n, n);
        }
    } else if (mode == 2) {
        int t = rnd.next(8, 24);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 1000000);
            int delta = rnd.next(-3, 5);
            addCase(cases, n, 2LL * n + delta);
        }
    } else if (mode == 3) {
        int t = rnd.next(6, 20);
        for (int i = 0; i < t; ++i) {
            int small = rnd.next(1, 8);
            int large = rnd.next(999999900, 1000000000);
            if (rnd.next(2) == 0) {
                addCase(cases, small, large);
            } else {
                addCase(cases, large, small);
            }
        }
    } else if (mode == 4) {
        int t = rnd.next(8, 24);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 1000000000);
            int span = rnd.next(0, 1000);
            addCase(cases, n, (long long)n + rnd.next(-span, span));
        }
    } else {
        int t = rnd.next(8, 30);
        for (int i = 0; i < t; ++i) {
            int bucket = rnd.next(4);
            int n, m;
            if (bucket == 0) {
                n = rnd.next(1, 100);
                m = rnd.next(1, 100);
            } else if (bucket == 1) {
                n = rnd.next(1, 1000000);
                m = rnd.next(1, 1000000);
            } else if (bucket == 2) {
                n = rnd.next(999999000, 1000000000);
                m = rnd.next(999999000, 1000000000);
            } else {
                n = rnd.next(1, 1000000000);
                m = rnd.next(1, 1000000000);
            }
            addCase(cases, n, m);
        }
    }

    if (rnd.next(2) == 0) {
        shuffle(cases.begin(), cases.end());
    }

    println((int)cases.size());
    for (auto [n, m] : cases) {
        println(n, m);
    }

    return 0;
}
