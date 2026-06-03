#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampTempo(int value) {
    return max(-10000, min(10000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (rnd.next(0, 4) == 0) {
        n = rnd.next(20, 35);
    } else {
        n = rnd.next(2, 15);
    }

    int q = rnd.next(1, min(50, n * (n + 1) / 2));
    vector<int> a(n);

    if (mode == 0) {
        a[0] = rnd.next(-10000, 10000);
    } else if (mode == 1) {
        int value = rnd.next(-10000, 10000);
        fill(a.begin(), a.end(), value);
    } else if (mode == 2) {
        int low = rnd.next(-10000, 0);
        int high = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 3) {
        a[0] = rnd.next(-5000, 5000);
        int stepLimit = rnd.next(0, 4000);
        for (int i = 1; i < n; ++i) {
            a[i] = clampTempo(a[i - 1] + rnd.next(-stepLimit, stepLimit));
        }
    } else if (mode == 4) {
        fill(a.begin(), a.end(), rnd.next(-20, 20));
        int spikes = rnd.next(1, min(n, 5));
        for (int i = 0; i < spikes; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(-10000, 10000);
        }
    } else {
        int lo = rnd.next(-10000, 5000);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    }

    vector<pair<int, int>> queries;
    queries.push_back({1, 1});
    queries.push_back({1, n});
    if (n > 1) {
        queries.push_back({n, n});
        queries.push_back({rnd.next(1, n - 1), n});
    }

    while ((int)queries.size() < q) {
        int l = rnd.next(1, n);
        int r = rnd.next(l, n);
        queries.push_back({l, r});
    }
    shuffle(queries.begin(), queries.end());

    println(n, q);
    println(a);
    for (int i = 0; i < q; ++i) {
        println(queries[i].first, queries[i].second);
    }

    return 0;
}
