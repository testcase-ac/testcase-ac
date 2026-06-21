#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampHeight(int value) {
    return max(1, min(1000000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(25, 60);
    } else {
        n = rnd.next(2, 18);
    }

    vector<int> h(n);
    if (mode == 0) {
        h[0] = rnd.any(vector<int>{1, 2, 999999, 1000000});
    } else if (mode == 1) {
        int cur = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 8);
            h[i] = clampHeight(cur);
        }
    } else if (mode == 2) {
        int cur = rnd.next(999900, 1000000);
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0, 8);
            h[i] = clampHeight(cur);
        }
    } else if (mode == 3) {
        int low = rnd.next(1, 20);
        int high = rnd.next(999980, 1000000);
        for (int i = 0; i < n; ++i) {
            h[i] = (i % 2 == 0 ? low + rnd.next(0, 5) : high - rnd.next(0, 5));
        }
    } else if (mode == 4) {
        int peak = rnd.next(0, n - 1);
        int base = rnd.next(1, 100);
        int step = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            h[i] = clampHeight(base + step * (n - abs(i - peak)) + rnd.next(0, 6));
        }
    } else if (mode == 5) {
        int value = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) h[i] = value;
    } else {
        int lo = rnd.next(1, 999950);
        int hi = rnd.next(lo, min(1000000, lo + rnd.next(0, 1000)));
        for (int i = 0; i < n; ++i) h[i] = rnd.next(lo, hi);
    }

    int q = rnd.next(1, min(60, max(1, n * 3)));
    vector<int> queries;
    queries.reserve(q);
    while ((int)queries.size() < q) {
        int choice = rnd.next(0, 5);
        if (choice == 0) {
            queries.push_back(1);
        } else if (choice == 1) {
            queries.push_back(n);
        } else if (choice == 2) {
            queries.push_back((n + 1) / 2);
        } else {
            queries.push_back(rnd.next(1, n));
        }
    }
    shuffle(queries.begin(), queries.end());

    println(n);
    println(h);
    println(q);
    for (int p : queries) println(p);

    return 0;
}
