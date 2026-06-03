#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

static void addEdge(vector<Edge>& edges, int a, int b, int w) {
    edges.push_back({a, b, w});
}

static void addTree(vector<Edge>& edges, set<pair<int, int>>& used, int n, int lo, int hi) {
    vector<int> order;
    for (int i = 1; i <= n; ++i) order.push_back(i);
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        int a = order[i];
        int b = order[rnd.next(0, i - 1)];
        addEdge(edges, a, b, rnd.next(lo, hi));
        used.insert(minmax(a, b));
    }
}

static void addUnusedSimpleEdges(vector<Edge>& edges, set<pair<int, int>>& used, int n, int count) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    count = min(count, (int)candidates.size());
    for (int i = 0; i < count; ++i) {
        auto [a, b] = candidates[i];
        addEdge(edges, a, b, rnd.next(1, 100));
        used.insert({a, b});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int s = 1;
    int t = n;
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(2, 10);
        s = 1;
        t = n;
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 15));
            used.insert({i, i + 1});
        }
        addUnusedSimpleEdges(edges, used, n, rnd.next(0, n));
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v == center) continue;
            addEdge(edges, center, v, rnd.next(1, 40));
            used.insert(minmax(center, v));
        }
        addUnusedSimpleEdges(edges, used, n, rnd.next(0, n));
        do {
            s = rnd.next(1, n);
            t = rnd.next(1, n);
        } while (s == t);
    } else if (mode == 2) {
        n = rnd.next(5, 12);
        addTree(edges, used, n, 20, 100);
        addUnusedSimpleEdges(edges, used, n, rnd.next(n, min(n * (n - 1) / 2 - (n - 1), 25)));
        do {
            s = rnd.next(1, n);
            t = rnd.next(1, n);
        } while (s == t);
    } else if (mode == 3) {
        n = rnd.next(3, 9);
        addTree(edges, used, n, 1, 20);
        vector<pair<int, int>> pairs;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) pairs.push_back({a, b});
        }
        shuffle(pairs.begin(), pairs.end());
        int duplicates = rnd.next(1, min(8, (int)pairs.size()));
        for (int i = 0; i < duplicates; ++i) {
            auto [a, b] = pairs[i];
            addEdge(edges, a, b, rnd.next(1, 100));
            addEdge(edges, a, b, rnd.next(1, 100));
        }
        do {
            s = rnd.next(1, n);
            t = rnd.next(1, n);
        } while (s == t);
    } else if (mode == 4) {
        n = rnd.next(6, 12);
        s = 1;
        t = n;
        int mid = rnd.next(2, n - 1);
        addEdge(edges, s, mid, rnd.next(1, 8));
        addEdge(edges, mid, t, rnd.next(1, 8));
        used.insert(minmax(s, mid));
        used.insert(minmax(mid, t));
        for (int v = 2; v < n; ++v) {
            if (v == mid) continue;
            int parent = rnd.next(1, v - 1);
            addEdge(edges, parent, v, rnd.next(30, 100));
            used.insert(minmax(parent, v));
        }
        if (!used.count({n - 1, n})) {
            addEdge(edges, n - 1, n, rnd.next(30, 100));
            used.insert({n - 1, n});
        }
        addUnusedSimpleEdges(edges, used, n, rnd.next(0, n));
    } else {
        n = rnd.next(2, 12);
        addTree(edges, used, n, 1, 100);
        int extraLimit = n * (n - 1) / 2 - (n - 1);
        addUnusedSimpleEdges(edges, used, n, rnd.next(0, min(extraLimit, 18)));
        do {
            s = rnd.next(1, n);
            t = rnd.next(1, n);
        } while (s == t);
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (Edge edge : edges) {
        if (rnd.next(0, 1)) swap(edge.a, edge.b);
        println(edge.a, edge.b, edge.w);
    }
    println(s, t);

    return 0;
}
