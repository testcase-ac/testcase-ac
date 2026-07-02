#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 4 ? 18 : 10);
    vector<int> price(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            price[i] = rnd.next(1, 8);
        } else if (mode == 1) {
            price[i] = rnd.next(80, 100);
        } else {
            price[i] = rnd.next(1, 100);
        }
    }

    vector<tuple<int, int, int>> edges;
    if (mode == 0) {
        for (int i = 0; i + 1 < n; ++i) {
            edges.emplace_back(i, i + 1, rnd.next(1, 25));
        }
        for (int i = 0; i + 2 < n; ++i) {
            if (rnd.next(0, 1)) {
                edges.emplace_back(i, i + 2, rnd.next(1, 40));
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < 0.45) {
                    edges.emplace_back(i, j, rnd.next(1, 100));
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                edges.emplace_back(i, i, rnd.next(1, 12));
            }
        }
        int extra = rnd.next(n, max(n, 2 * n + 3));
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(0, n - 1);
            int v = rnd.next(0, n - 1);
            edges.emplace_back(u, v, rnd.next(1, 30));
        }
    } else if (mode == 3) {
        int split = max(1, n / 2);
        for (int i = 0; i + 1 < split; ++i) {
            edges.emplace_back(i, i + 1, rnd.next(1, 35));
        }
        for (int i = split; i + 1 < n; ++i) {
            edges.emplace_back(i, i + 1, rnd.next(1, 35));
        }
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int lo = rnd.next(0, 1) ? split : 0;
            int hi = lo == 0 ? max(0, split - 1) : n - 1;
            if (lo <= hi) {
                edges.emplace_back(rnd.next(lo, hi), rnd.next(lo, hi), rnd.next(1, 45));
            }
        }
    } else {
        int extra = rnd.next(n, min(100, n * n));
        for (int i = 0; i < extra; ++i) {
            edges.emplace_back(rnd.next(0, n - 1), rnd.next(0, n - 1), rnd.next(1, 100));
        }
    }

    shuffle(edges.begin(), edges.end());
    int m = min<int>(edges.size(), 10000);

    int q = rnd.next(1, 12);
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int c;
        if (i == 0) {
            c = 1;
        } else if (i == 1) {
            c = 100;
        } else {
            c = rnd.next(1, 100);
        }
        int s = rnd.next(0, n - 1);
        int e = rnd.next(0, n - 1);
        if (mode == 3 && n > 1 && i % 3 == 0) {
            s = rnd.next(0, max(0, n / 2 - 1));
            e = rnd.next(n / 2, n - 1);
        }
        queries.emplace_back(c, s, e);
    }

    println(n, m);
    println(price);
    for (int i = 0; i < m; ++i) {
        int u, v, d;
        tie(u, v, d) = edges[i];
        println(u, v, d);
    }
    println(q);
    for (auto [c, s, e] : queries) {
        println(c, s, e);
    }

    return 0;
}
