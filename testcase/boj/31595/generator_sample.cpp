#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using ull = unsigned long long;

vector<int> popcountWindow(ull x, int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = __builtin_popcountll(x + (ull)i);
    }
    return a;
}

ull randomBase() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return (ull)rnd.next(0, 80);
    if (mode == 1) {
        int k = rnd.next(1, 20);
        ull high = 1ULL << k;
        ull delta = (ull)rnd.next(0, min(40, (int)high - 1));
        return high - 1 - delta;
    }
    if (mode == 2) {
        int k = rnd.next(1, 50);
        return (1ULL << k) - 1;
    }
    if (mode == 3) {
        int k = rnd.next(2, 50);
        return (1ULL << k) + (ull)rnd.next(0, 80);
    }

    ull x = 0;
    int bits = rnd.next(0, 60);
    vector<int> positions(60);
    for (int i = 0; i < 60; ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < bits; ++i) x |= 1ULL << positions[i];
    return x;
}

vector<int> randomArray(int n) {
    vector<int> a(n);
    int lo = rnd.next(0, 20);
    int hi = rnd.next(lo, 60);
    for (int& value : a) value = rnd.next(lo, hi);
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 24);
    vector<vector<int>> tests;
    tests.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0) n = 1;
        else if (mode == 1) n = rnd.next(2, 6);
        else if (mode == 2) n = rnd.next(7, 20);
        else n = rnd.next(2, 60);

        vector<int> a;
        if (mode <= 2) {
            a = popcountWindow(randomBase(), n);
        } else if (mode == 3) {
            a = popcountWindow(randomBase(), n);
            int changes = rnd.next(1, min(3, n));
            for (int i = 0; i < changes; ++i) {
                int pos = rnd.next(0, n - 1);
                int delta = rnd.any(vector<int>{-2, -1, 1, 2, 10});
                a[pos] = max(0, min(60, a[pos] + delta));
            }
        } else if (mode == 4) {
            a = randomArray(n);
        } else {
            a.assign(n, rnd.next(0, 60));
            if (n >= 2 && rnd.next(0, 1)) a[rnd.next(0, n - 1)] = rnd.next(0, 60);
        }

        tests.push_back(a);
    }

    println((int)tests.size());
    for (const vector<int>& a : tests) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
