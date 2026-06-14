#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(-1000000, min(1000000, x));
}

vector<int> makeArray(int n, int mode) {
    vector<int> a;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(-5, 5));
    } else if (mode == 1) {
        vector<int> pool = {-3, -2, -1, 0, 1, 2, 3};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 2) {
        vector<int> triples = {-1000000, 0, 1000000, -999999, -1, 1000000};
        while ((int)a.size() < n) a.push_back(rnd.any(triples));
    } else if (mode == 3) {
        int step = rnd.next(1, 9);
        int start = -step * (n / 2);
        for (int i = 0; i < n; ++i) a.push_back(clampValue(start + i * step));
        shuffle(a.begin(), a.end());
    } else {
        int lo = rnd.next(-100, 0);
        int hi = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    return a;
}

pair<int, int> makeQuery(int n, int kind) {
    if (kind == 0) return {1, n};
    if (kind == 1) {
        int x = rnd.next(1, n);
        return {x, x};
    }
    if (kind == 2) {
        int len = rnd.next(1, min(n, 4));
        int l = rnd.next(1, n - len + 1);
        return {l, l + len - 1};
    }
    if (kind == 3 && n >= 3) {
        int len = rnd.next(3, n);
        int l = rnd.next(1, n - len + 1);
        return {l, l + len - 1};
    }

    int l = rnd.next(1, n);
    int r = rnd.next(l, n);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 2) {
        n = rnd.next(6, 30);
    } else {
        n = rnd.next(3, 40);
    }

    int q = rnd.next(1, min(35, n * 3 + 5));
    vector<int> a = makeArray(n, mode);

    println(n, q);
    println(a);

    for (int i = 0; i < q; ++i) {
        int kind = (i < 4 ? i : rnd.next(0, 4));
        pair<int, int> query = makeQuery(n, kind);
        println(query.first, query.second);
    }

    return 0;
}
