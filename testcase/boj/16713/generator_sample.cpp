#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    int q = rnd.next(1, 36);

    if (mode == 1) {
        n = rnd.next(1, 8);
        q = rnd.next(20, 60);
    } else if (mode == 2) {
        n = rnd.next(15, 45);
        q = rnd.next(1, 12);
    } else if (mode == 3) {
        n = rnd.next(2, 32);
        q = rnd.next(15, 45);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        q = rnd.next(1, 10);
    } else if (mode == 5) {
        n = rnd.next(25, 80);
        q = rnd.next(25, 80);
    }

    vector<int> a(n);
    int pattern = rnd.next(0, 5);
    int base = rnd.next(0, 20);
    int bit = 1 << rnd.next(0, 29);
    for (int i = 0; i < n; ++i) {
        if (pattern == 0) {
            a[i] = rnd.next(0, 20);
        } else if (pattern == 1) {
            a[i] = base;
        } else if (pattern == 2) {
            a[i] = (i % 2 == 0 ? base : base ^ bit);
        } else if (pattern == 3) {
            a[i] = rnd.next(0, 3) == 0 ? 0 : rnd.next(0, 1000000000);
        } else if (pattern == 4) {
            a[i] = i == 0 ? base : (a[i - 1] ^ rnd.next(0, 31));
        } else {
            a[i] = rnd.any(vector<int>{0, 1, 2, 3, 7, 15, 31, 1000000000});
        }
    }

    vector<pair<int, int>> queries;
    auto addQuery = [&](int l, int r) {
        if (l > r) swap(l, r);
        queries.push_back({l, r});
    };

    if (n >= 1) {
        addQuery(1, n);
        addQuery(1, 1);
        addQuery(n, n);
    }

    while ((int)queries.size() < q) {
        int shape = rnd.next(0, 6);
        if (shape == 0) {
            int x = rnd.next(1, n);
            addQuery(x, x);
        } else if (shape == 1) {
            addQuery(1, rnd.next(1, n));
        } else if (shape == 2) {
            addQuery(rnd.next(1, n), n);
        } else if (shape == 3 && !queries.empty()) {
            queries.push_back(rnd.any(queries));
        } else if (shape == 4) {
            int len = rnd.next(1, min(n, 5));
            int l = rnd.next(1, n - len + 1);
            addQuery(l, l + len - 1);
        } else {
            addQuery(rnd.next(1, n), rnd.next(1, n));
        }
    }

    queries.resize(q);
    shuffle(queries.begin(), queries.end());

    println(n, q);
    println(a);
    for (auto [l, r] : queries) {
        println(l, r);
    }

    return 0;
}
