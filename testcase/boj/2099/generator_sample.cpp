#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int otherVertex(int i, int n) {
    int v = rnd.next(1, n - 1);
    if (v >= i) ++v;
    return v;
}

int wrapNext(int i, int n) {
    return i == n ? 1 : i + 1;
}

int wrapPrev(int i, int n) {
    return i == 1 ? n : i - 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    int m = rnd.next(1, min(40, n * n));
    int k;
    if (rnd.next(0, 3) == 0) {
        k = rnd.next(1, 8);
    } else {
        k = rnd.next(1, 1000000);
    }

    vector<pair<int, int>> choice(n + 1);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            int v = wrapNext(i, n);
            choice[i] = {v, v};
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            choice[i] = {wrapNext(i, n), wrapPrev(i, n)};
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i <= n; ++i) {
            int lo = i <= split ? 1 : split + 1;
            int hi = i <= split ? split : n;
            vector<int> pool;
            for (int v = lo; v <= hi; ++v) {
                if (v != i) pool.push_back(v);
            }
            if (pool.empty()) {
                choice[i] = {otherVertex(i, n), otherVertex(i, n)};
            } else {
                choice[i] = {rnd.any(pool), rnd.any(pool)};
            }
        }
    } else if (mode == 3) {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        for (int pos = 0; pos < n; ++pos) {
            int i = order[pos];
            int forward = order[(pos + 1) % n];
            int jump = order[(pos + rnd.next(1, n - 1)) % n];
            choice[i] = {forward, jump};
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            choice[i] = {otherVertex(i, n), otherVertex(i, n)};
        }
    }

    println(n, k, m);
    for (int i = 1; i <= n; ++i) {
        println(choice[i].first, choice[i].second);
    }

    vector<pair<int, int>> queries;
    for (int i = 1; i <= n; ++i) {
        queries.push_back({i, i});
        queries.push_back({i, choice[i].first});
        queries.push_back({i, choice[i].second});
    }
    while ((int)queries.size() < m) {
        queries.push_back({rnd.next(1, n), rnd.next(1, n)});
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(m);
    for (auto [a, b] : queries) {
        println(a, b);
    }

    return 0;
}
