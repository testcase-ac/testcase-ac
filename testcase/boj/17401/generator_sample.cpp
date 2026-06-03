#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

vector<pair<int, int>> allPairs(int n) {
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            pairs.push_back({a, b});
        }
    }
    return pairs;
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int c) {
    if (used.insert({a, b}).second) {
        edges.push_back({a, b, c});
    }
}

int randomWeight(int mode) {
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(1, 5);
    if (mode == 2) return rnd.next(900, 1000);
    return rnd.next(1, 1000);
}

vector<Edge> makeMap(int n, int mode) {
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        return edges;
    }

    if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(2)) {
                addEdge(edges, used, i, i, randomWeight(1));
            }
        }
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, randomWeight(1));
        }
        if (rnd.next(2)) {
            addEdge(edges, used, n, 1, randomWeight(1));
        }
    } else if (mode == 3) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());
        for (int i = 0; i < n; ++i) {
            addEdge(edges, used, p[i], p[(i + 1) % n], randomWeight(1));
        }
    } else {
        vector<pair<int, int>> pairs = allPairs(n);
        shuffle(pairs.begin(), pairs.end());
        int maxEdges = n * n;
        int m = mode == 4 ? rnd.next(1, min(maxEdges, 2 * n))
                          : rnd.next(max(1, maxEdges / 2), maxEdges);
        for (int i = 0; i < m; ++i) {
            addEdge(edges, used, pairs[i].first, pairs[i].second, randomWeight(mode == 5 ? 2 : 3));
        }
    }

    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(4);
    int n = sizeMode == 0 ? rnd.next(2, 4)
                          : sizeMode == 1 ? rnd.next(5, 8)
                                          : rnd.next(9, 12);
    int t = rnd.next(1, 8);

    long long d;
    int dMode = rnd.next(6);
    if (dMode == 0) {
        d = 0;
    } else if (dMode == 1) {
        d = rnd.next(1, t);
    } else if (dMode == 2) {
        d = rnd.next(t, 4 * t);
    } else if (dMode == 3) {
        d = rnd.next(1000, 100000);
    } else if (dMode == 4) {
        d = 1000000000LL - rnd.next(0, 1000);
    } else {
        d = 1LL * rnd.next(1, 1000000) * t + rnd.next(0, t - 1);
    }

    println(t, n, d);

    for (int i = 0; i < t; ++i) {
        int mode;
        if (i == 0 && rnd.next(4) == 0) {
            mode = 0;
        } else {
            mode = rnd.next(1, 6);
        }
        vector<Edge> edges = makeMap(n, mode);
        println(static_cast<int>(edges.size()));
        for (const auto& [a, b, c] : edges) {
            println(a, b, c);
        }
    }

    return 0;
}
