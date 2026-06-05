#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = (mode == 0 ? rnd.next(1, 4) : rnd.next(2, 30));
    int k = rnd.next(1, 40);

    vector<int> a(n);
    if (mode == 0) {
        for (int& x : a) x = rnd.next(-3, 3);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a[i] = i - n / 2;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = n / 2 - i;
    } else if (mode == 3) {
        for (int& x : a) x = rnd.any(vector<int>{-10000, -1, 0, 1, 10000});
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? rnd.next(-20, -1) : rnd.next(1, 20));
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) a[i] = i + 1;
        shuffle(a.begin(), a.end());
    } else {
        int lo = rnd.next(-100, 0);
        int hi = rnd.next(0, 100);
        for (int& x : a) x = rnd.next(lo, hi);
    }

    vector<pair<int, int>> ops;
    ops.reserve(k);
    for (int i = 0; i < k; ++i) {
        int pattern = rnd.next(0, 5);
        int x, y;
        if (pattern == 0) {
            x = n;
            y = rnd.next(1, n);
        } else if (pattern == 1) {
            x = rnd.next(1, n);
            y = n;
        } else if (pattern == 2) {
            x = y = rnd.next(1, n);
        } else if (pattern == 3) {
            x = rnd.next(1, min(n, 3));
            y = rnd.next(1, min(n, 3));
        } else if (pattern == 4) {
            x = n - rnd.next(0, min(n - 1, 4));
            y = n - rnd.next(0, min(n - 1, 4));
        } else {
            x = rnd.next(1, n);
            y = rnd.next(1, n);
        }
        ops.push_back({x, y});
    }

    println(n);
    println(a);
    println(k);
    for (auto [x, y] : ops) println(x, y);

    return 0;
}
