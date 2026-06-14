#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

struct Edge {
    int u;
    int v;
    int r;
    int c;
    bool vertical;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    int m;
    if (mode == 0) {
        n = 2;
        m = rnd.next(2, 14);
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        m = 2;
    } else if (mode == 2) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
    } else if (mode == 3) {
        n = rnd.next(4, 9);
        m = rnd.next(4, 9);
    } else {
        n = rnd.next(2, 8);
        m = rnd.next(2, 12);
    }

    int t = rnd.next(1, 30);
    vector<vector<int>> a(n - 1, vector<int>(m, 1));
    vector<vector<int>> b(n, vector<int>(m - 1, 1));
    vector<Edge> edges;

    for (int i = 0; i + 1 < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = i * m + j;
            edges.push_back({u, u + m, i, j, true});
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 1 < m; ++j) {
            int u = i * m + j;
            edges.push_back({u, u + 1, i, j, false});
        }
    }

    shuffle(edges.begin(), edges.end());
    Dsu dsu(n * m);
    for (const Edge& edge : edges) {
        if (!dsu.unite(edge.u, edge.v)) {
            continue;
        }
        if (edge.vertical) {
            a[edge.r][edge.c] = 0;
        } else {
            b[edge.r][edge.c] = 0;
        }
    }

    int k = rnd.next(1, 25);
    println(n, m, t);
    for (const vector<int>& row : a) {
        println(row);
    }
    for (const vector<int>& row : b) {
        println(row);
    }

    println(k);
    for (int i = 0; i < k; ++i) {
        int s = rnd.next(1, t);
        int e = rnd.next(s, t);
        int r1 = rnd.next(0, n - 1);
        int c1 = rnd.next(0, m - 1);
        int r2 = rnd.next(0, n - 1);
        int c2 = rnd.next(0, m - 1);
        int v = rnd.next(1, 1000);
        println(s, e, r1, c1, r2, c2, v);
    }

    return 0;
}
