#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int chooseSize(int mode) {
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 5);
    if (mode == 2) return rnd.next(6, 20);
    if (mode == 3) return rnd.next(21, 80);
    if (mode == 4) return rnd.next(81, 250);
    return rnd.next(251, 800);
}

vector<int64> makeSequence(int n, int mode) {
    vector<int64> a(n);
    if (mode == 0) {
        fill(a.begin(), a.end(), rnd.next(-5, 5));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(-20, 20);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(1, 100);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 5) == 0 ? rnd.next(-1000000000, 1000000000) : rnd.next(-1000, 1000);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 1) ? 1000000000LL : -1000000000LL;
    } else if (mode == 5) {
        int64 cur = rnd.next(-200, 200);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(-15, 15);
            a[i] = cur;
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            int block = (i / max(1, rnd.next(1, 7))) % 3;
            if (block == 0) a[i] = rnd.next(1, 100);
            else if (block == 1) a[i] = -rnd.next(1, 100);
            else a[i] = rnd.next(-3, 3);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (i == 0 || i + 1 == n) a[i] = rnd.next(-1000000000, 1000000000);
            else a[i] = rnd.next(-50, 50);
        }
    }
    return a;
}

vector<int64> makeQueries(int q, int mode) {
    vector<int64> x;
    vector<int64> edge = {-1000000000LL, -999999999LL, -1000000LL, -1000LL, -1LL, 0LL,
                          1LL, 1000LL, 1000000LL, 999999999LL, 1000000000LL};

    if (mode == 0) {
        for (int i = 0; i < q; ++i) x.push_back(edge[i % (int)edge.size()]);
    } else if (mode == 1) {
        int64 v = rnd.next(-10, 10);
        x.assign(q, v);
    } else if (mode == 2) {
        int64 start = rnd.next(-100, 100);
        for (int i = 0; i < q; ++i) x.push_back(max(-1000000000LL, min(1000000000LL, start + i - q / 2)));
    } else if (mode == 3) {
        for (int i = 0; i < q; ++i) x.push_back(rnd.next(-1000, 1000));
    } else if (mode == 4) {
        for (int i = 0; i < q; ++i) x.push_back(rnd.next(-1000000000, 1000000000));
    } else {
        for (int i = 0; i < q; ++i) x.push_back(rnd.any(edge));
    }

    int orderMode = rnd.next(0, 3);
    if (orderMode == 0) sort(x.begin(), x.end());
    else if (orderMode == 1) sort(x.rbegin(), x.rend());
    else if (orderMode == 2) shuffle(x.begin(), x.end());
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = chooseSize(rnd.next(0, 5));
    int q = chooseSize(rnd.next(0, 4));
    if (rnd.next(0, 9) == 0) q = n;

    vector<int64> a = makeSequence(n, rnd.next(0, 7));
    vector<int64> x = makeQueries(q, rnd.next(0, 5));

    println(n, q);
    println(a);
    println(x);
    return 0;
}
