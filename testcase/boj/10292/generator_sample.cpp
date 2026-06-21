#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Edge = pair<int, int>;

void addEdge(set<Edge>& used, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    used.insert({a, b});
}

vector<Edge> relabelAndShuffle(int n, const set<Edge>& used) {
    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    vector<Edge> edges;
    for (auto [a, b] : used) {
        int u = label[a];
        int v = label[b];
        if (rnd.next(2) == 0) {
            swap(u, v);
        }
        edges.push_back({u, v});
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

set<Edge> makePath(int n) {
    set<Edge> edges;
    for (int i = 1; i < n; ++i) {
        addEdge(edges, i, i + 1);
    }
    return edges;
}

set<Edge> makeCycle(int n) {
    set<Edge> edges = makePath(n);
    if (n >= 3) {
        addEdge(edges, 1, n);
    }
    return edges;
}

set<Edge> makeClique(int n) {
    set<Edge> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            addEdge(edges, i, j);
        }
    }
    return edges;
}

set<Edge> makeTwoBlocks(int n) {
    set<Edge> edges;
    int left = rnd.next(3, n - 2);
    int cut = left;

    for (int i = 1; i <= left; ++i) {
        addEdge(edges, i, i == left ? 1 : i + 1);
    }
    for (int i = cut; i <= n; ++i) {
        addEdge(edges, i, i == n ? cut : i + 1);
    }

    return edges;
}

set<Edge> makeConnectedRandom(int n) {
    set<Edge> edges;
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        int parent = order[rnd.next(i)];
        addEdge(edges, order[i], parent);
    }

    int maxEdges = n * (n - 1) / 2;
    int target = rnd.next(n - 1, min(maxEdges, n + rnd.next(0, n)));
    while ((int)edges.size() < target) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (a != b) {
            addEdge(edges, a, b);
        }
    }

    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(6);
        int n = 1;
        set<Edge> used;

        if (mode == 0) {
            n = 1;
        } else if (mode == 1) {
            n = rnd.next(2, 12);
            used = makePath(n);
        } else if (mode == 2) {
            n = rnd.next(3, 12);
            used = makeCycle(n);
        } else if (mode == 3) {
            n = rnd.next(3, 9);
            used = makeClique(n);
        } else if (mode == 4) {
            n = rnd.next(5, 12);
            used = makeTwoBlocks(n);
        } else {
            n = rnd.next(2, 12);
            used = makeConnectedRandom(n);
        }

        vector<Edge> edges = relabelAndShuffle(n, used);
        println(n, (int)edges.size());
        for (auto [a, b] : edges) {
            println(a, b);
        }
    }

    return 0;
}
