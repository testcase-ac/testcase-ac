#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

vector<int> makeValid(int n) {
    vector<int> a;
    vector<int> active;
    a.reserve(n);

    for (int i = 0; i < n; ++i) {
        bool startNew = active.empty() || rnd.next(100) < 45;
        if (startNew) {
            a.push_back(1);
            active.push_back(1);
            continue;
        }

        int idx;
        if (rnd.next(100) < 65) {
            idx = (int)active.size() - 1;
        } else {
            idx = rnd.next((int)active.size());
        }

        int nextValue = active[idx] + 1;
        a.push_back(nextValue);
        active.resize(idx);
        active.push_back(nextValue);
    }

    return a;
}

vector<int> makeInvalidJump(int n) {
    vector<int> a = makeValid(n);
    if (n == 1) {
        return a;
    }

    int pos = rnd.next(n);
    int replacement = rnd.next(2, n);
    if (pos == 0) {
        a[pos] = replacement;
        return a;
    }

    vector<int> seen(n + 1, 0);
    for (int i = 0; i < pos; ++i) {
        seen[a[i]] = 1;
    }

    vector<int> candidates;
    for (int value = 2; value <= n; ++value) {
        if (!seen[value - 1]) {
            candidates.push_back(value);
        }
    }
    if (!candidates.empty()) {
        a[pos] = rnd.any(candidates);
    } else {
        a[pos] = n;
    }
    return a;
}

vector<int> makePattern(int n) {
    vector<int> a(n);
    int mode = rnd.next(5);
    if (mode == 0) {
        fill(a.begin(), a.end(), 1);
    } else if (mode == 1) {
        iota(a.begin(), a.end(), 1);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? 1 : 2);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = n - i;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, min(n, 4));
        }
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 10);
    vector<vector<int>> tests;
    tests.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 20);
        int mode = rnd.next(100);

        if (mode < 45) {
            tests.push_back(makeValid(n));
        } else if (mode < 75) {
            tests.push_back(makeInvalidJump(n));
        } else {
            tests.push_back(makePattern(n));
        }
    }

    println((int)tests.size());
    for (const vector<int>& a : tests) {
        println((int)a.size());
        println(a);
    }

    return 0;
}
