#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<long long> randomDistinct(int n, long long lo, long long hi) {
    set<long long> used;
    while ((int)used.size() < n) {
        used.insert(rnd.next(lo, hi));
    }
    return vector<long long>(used.begin(), used.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
    } else if (mode == 2) {
        n = rnd.next(10, 80);
    } else if (mode == 3) {
        n = rnd.next(30, 160);
    } else if (mode == 4) {
        n = rnd.next(100, 500);
    } else {
        n = rnd.next(1000, 2000);
    }

    int kMode = rnd.next(0, 5);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = rnd.next(1, min(n, 3));
    } else if (kMode == 3) {
        k = rnd.next(max(1, n - 3), n);
    } else {
        k = rnd.next(1, n);
    }

    vector<long long> a;
    int pattern = rnd.next(0, 5);
    if (pattern == 0) {
        long long start = rnd.next(1LL, 1000LL);
        long long step = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) a.push_back(start + step * i);
    } else if (pattern == 1) {
        long long start = rnd.next(1LL, 1000LL);
        long long step = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) a.push_back(start + step * i);
        reverse(a.begin(), a.end());
    } else if (pattern == 2) {
        a = randomDistinct(n, 1, 1000000000LL);
        shuffle(a.begin(), a.end());
    } else if (pattern == 3) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a.push_back(1 + i / 2);
            } else {
                a.push_back(1000000000LL - i / 2);
            }
        }
    } else {
        a = randomDistinct(n, 1, 3LL * n + 20);
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    }

    println(n, k);
    println(a);

    return 0;
}
