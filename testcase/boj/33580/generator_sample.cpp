#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i - 1, i});
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({1, i});
    }
    return edges;
}

vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i / 2, i});
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({rnd.next(1, i - 1), i});
    }
    return edges;
}

vector<pair<int, int>> makeCaterpillar(int n) {
    int spine = rnd.next(2, n - 1);
    vector<pair<int, int>> edges = makePath(spine);
    for (int i = spine + 1; i <= n; ++i) {
        edges.push_back({rnd.next(1, spine), i});
    }
    return edges;
}

vector<int> makeCatRoute(int n, int t, const vector<pair<int, int>>& edges) {
    int mode = rnd.next(0, 5);
    vector<int> c;

    if (mode == 0) {
        int x = rnd.next(1, n);
        c.assign(t, x);
    } else if (mode == 1) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        while (b == a) {
            b = rnd.next(1, n);
        }
        for (int i = 0; i < t; ++i) {
            c.push_back((i % 2 == 0) ? a : b);
        }
    } else if (mode == 2) {
        vector<vector<int>> adj(n + 1);
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int cur = rnd.next(1, n);
        for (int i = 0; i < t; ++i) {
            c.push_back(cur);
            if (!adj[cur].empty() && rnd.next(0, 1) == 1) {
                cur = rnd.any(adj[cur]);
            }
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < t; ++i) {
            c.push_back(rnd.next(lo, hi));
        }
    } else {
        for (int i = 0; i < t; ++i) {
            c.push_back(rnd.next(1, n));
        }
    }

    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 14);
    int t = rnd.next(1, 18);
    int treeMode = rnd.next(0, 4);

    vector<pair<int, int>> edges;
    if (treeMode == 0) {
        edges = makePath(n);
    } else if (treeMode == 1) {
        edges = makeStar(n);
    } else if (treeMode == 2) {
        edges = makeBinaryTree(n);
    } else if (treeMode == 3) {
        edges = makeCaterpillar(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end());

    for (auto& [u, v] : edges) {
        u = perm[u];
        v = perm[v];
        if (rnd.next(0, 1) == 1) {
            swap(u, v);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> cats = makeCatRoute(n, t, edges);
    for (int& x : cats) {
        x = perm[x];
    }

    println(n, t);
    for (auto [u, v] : edges) {
        println(u, v);
    }
    println(cats);

    return 0;
}
