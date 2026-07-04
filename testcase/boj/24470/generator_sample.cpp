#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, mode == 1 ? 10 : 8);
    int mLimit = min(60, n * n + 20);
    vector<tuple<int, int, int>> edges;

    auto addEdge = [&](int a, int b, int w) {
        edges.emplace_back(a, b, w);
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, rnd.next(1, 30));
            if (rnd.next(0, 1)) addEdge(i + 1, i, rnd.next(1, 30));
        }
        int extra = rnd.next(0, n + 3);
        for (int i = 0; i < extra; ++i) {
            addEdge(rnd.next(1, n), rnd.next(1, n), rnd.next(1, 100));
        }
    } else if (mode == 1) {
        double density = rnd.next(0.25, 0.75);
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (a != b && rnd.next() < density) {
                    addEdge(a, b, rnd.next(1, 200));
                }
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(n, min(mLimit, n * 3));
        for (int i = 0; i < base; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            int w = rnd.next(1, 20);
            addEdge(a, b, w);
            if ((int)edges.size() < mLimit && rnd.next(0, 2) == 0) {
                addEdge(a, b, rnd.next(1, 20));
            }
        }
    } else {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i <= split; ++i) {
            int next = i == split ? 1 : i + 1;
            addEdge(i, next, rnd.next(1, 50));
        }
        for (int i = split + 1; i <= n; ++i) {
            int next = i == n ? split + 1 : i + 1;
            addEdge(i, next, rnd.next(1, 50));
        }
        int bridges = rnd.next(0, 2);
        for (int i = 0; i < bridges; ++i) {
            addEdge(rnd.next(1, split), rnd.next(split + 1, n), rnd.next(1, 80));
        }
    }

    while ((int)edges.size() < 1) {
        addEdge(rnd.next(1, n), rnd.next(1, n), rnd.next(1, 100));
    }
    shuffle(edges.begin(), edges.end());
    if ((int)edges.size() > mLimit) edges.resize(mLimit);

    int kMode = rnd.next(0, 4);
    int k;
    if (kMode == 0) k = 1;
    else if (kMode == 1) k = rnd.next(2, n);
    else if (kMode == 2) k = rnd.next(n, n * n);
    else if (kMode == 3) k = 1000000000;
    else k = rnd.next(1, 5);

    int q = rnd.next(n, min(n * n, n + 10));
    vector<pair<int, int>> queries;
    for (int i = 1; i <= n && (int)queries.size() < q; ++i) {
        if (rnd.next(0, 2) == 0) queries.push_back({i, i});
    }
    while ((int)queries.size() < q) {
        queries.push_back({rnd.next(1, n), rnd.next(1, n)});
    }
    shuffle(queries.begin(), queries.end());

    println(n, (int)edges.size());
    for (auto [a, b, w] : edges) {
        println(a, b, w);
    }
    println(k, q);
    for (auto [c, d] : queries) {
        println(c, d);
    }

    return 0;
}
