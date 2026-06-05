#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

int nextCost(int mode) {
    if (mode == 0) return rnd.next(1, 8);
    if (mode == 1) return rnd.next(9000, 10000);
    if (mode == 2) return rnd.any(vector<int>{1, 2, 9999, 10000});
    return rnd.next(1, 10000);
}

pair<int, int> randomPair(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) ++b;
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 15);
    int maxSimple = n * (n - 1) / 2;
    int m = rnd.next(1, min(45, maxSimple + 12));

    vector<Edge> edges;
    vector<pair<int, int>> pairs;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            pairs.push_back({i, j});
        }
    }
    shuffle(pairs.begin(), pairs.end());

    int costMode = rnd.next(0, 3);

    if (mode == 0) {
        n = rnd.next(2, 10);
        m = rnd.next(1, min(2 * n, 30));
        for (int i = 1; i < n && (int)edges.size() < m; ++i) {
            edges.push_back({i, i + 1, nextCost(costMode)});
        }
    } else if (mode == 1) {
        m = rnd.next(max(1, maxSimple / 2), min(maxSimple, 45));
        for (int i = 0; i < m; ++i) {
            edges.push_back({pairs[i].first, pairs[i].second, nextCost(costMode)});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(n, 35);
        auto base = randomPair(n);
        for (int i = 0; i < m; ++i) {
            pair<int, int> p = rnd.next(0, 99) < 65 ? base : randomPair(n);
            edges.push_back({p.first, p.second, nextCost(costMode)});
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i <= split && (int)edges.size() < m; ++i) {
            for (int j = i + 1; j <= split && (int)edges.size() < m; ++j) {
                if (rnd.next(0, 99) < 55) edges.push_back({i, j, nextCost(costMode)});
            }
        }
        for (int i = split + 1; i <= n && (int)edges.size() < m; ++i) {
            for (int j = i + 1; j <= n && (int)edges.size() < m; ++j) {
                if (rnd.next(0, 99) < 55) edges.push_back({i, j, nextCost(costMode)});
            }
        }
    } else {
        m = rnd.next(1, min(40, maxSimple + n));
    }

    while ((int)edges.size() < m) {
        auto p = randomPair(n);
        edges.push_back({p.first, p.second, nextCost(costMode)});
    }

    shuffle(edges.begin(), edges.end());

    vector<int> escape(n);
    int escapeMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (escapeMode == 0) {
            escape[i] = rnd.next(1, 8);
        } else if (escapeMode == 1) {
            escape[i] = rnd.next(9000, 10000);
        } else if (escapeMode == 2) {
            escape[i] = i % 2 == 0 ? rnd.next(1, 5) : rnd.next(5000, 10000);
        } else if (escapeMode == 3) {
            escape[i] = rnd.any(vector<int>{1, 2, 9999, 10000});
        } else {
            escape[i] = rnd.next(1, 10000);
        }
    }

    println(n, (int)edges.size());
    for (const Edge& e : edges) {
        println(e.a, e.b, e.c);
    }
    println(escape);

    return 0;
}
