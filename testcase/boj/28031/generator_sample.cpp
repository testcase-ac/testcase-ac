#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 100000000;

int clampValue(int value) {
    return max(0, min(MAX_A, value));
}

int nearValue(int value) {
    int delta = rnd.next(-5, 5);
    return clampValue(value + delta);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(5, 20);
    } else if (mode == 3) {
        n = rnd.next(4, 18);
    } else {
        n = rnd.next(10, 40);
    }

    vector<int> a(n);
    if (mode == 0) {
        a[0] = rnd.any(vector<int>{0, 1, MAX_A - 1, MAX_A});
    } else if (mode == 1) {
        int base = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) a[i] = base;
    } else if (mode == 2) {
        int start = rnd.next(0, 30);
        int step = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) a[i] = start + i * step;
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 3) {
        vector<int> pool = {0, 1, 2, MAX_A - 2, MAX_A - 1, MAX_A};
        for (int i = 0; i < n; ++i) a[i] = rnd.any(pool);
    } else {
        int hi = rnd.any(vector<int>{10, 100, 1000, MAX_A});
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, hi);
    }

    if (mode >= 2 && rnd.next(0, 1)) shuffle(a.begin(), a.end());

    int q = rnd.next(1, max(1, min(50, n * 3)));
    vector<pair<int, int>> queries;
    for (int qi = 0; qi < q; ++qi) {
        int idx = rnd.next(1, n);
        int replacement;
        int qmode = rnd.next(0, 5);
        if (qmode == 0) {
            replacement = a[idx - 1];
        } else if (qmode == 1) {
            replacement = nearValue(a[idx - 1]);
        } else if (qmode == 2) {
            replacement = rnd.any(vector<int>{0, 1, MAX_A - 1, MAX_A});
        } else if (qmode == 3) {
            replacement = rnd.any(a);
        } else {
            replacement = rnd.next(0, rnd.any(vector<int>{20, 1000, MAX_A}));
        }
        queries.push_back({idx, replacement});
    }

    println(n);
    println(a);
    println(q);
    for (auto [idx, replacement] : queries) println(idx, replacement);

    return 0;
}
