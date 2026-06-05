#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int h;
};

int randomHeight(int mode, int i) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(999900, 1000000);
    if (mode == 2) return (i % 2 == 0 ? rnd.next(1, 5) : rnd.next(50, 120));
    return rnd.next(1, 1000000);
}

void addEdge(vector<Edge>& edges, int u, int v, int h) {
    if (u != v) edges.push_back({u, v, h});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    int heightMode = rnd.next(4);
    vector<Edge> edges;

    if (mode == 0) {
        int chainEnd = rnd.next(2, n);
        for (int i = 1; i < chainEnd; ++i) {
            addEdge(edges, i, i + 1, randomHeight(heightMode, i));
            if (rnd.next(3) == 0) addEdge(edges, i + 1, i, randomHeight(heightMode, i + n));
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            addEdge(edges, i, i == n ? 1 : i + 1, randomHeight(heightMode, i));
        }
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(edges, u, v, randomHeight(heightMode, i + n));
        }
    } else if (mode == 2) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next(100) < 35) {
                    addEdge(edges, u, v, randomHeight(heightMode, u * n + v));
                }
            }
        }
    } else if (mode == 3) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v == center) continue;
            if (rnd.next(2)) addEdge(edges, center, v, randomHeight(heightMode, v));
            else addEdge(edges, v, center, randomHeight(heightMode, v));
        }
    } else {
        int pairCount = rnd.next(1, min(8, n * (n - 1)));
        for (int i = 0; i < pairCount; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            int copies = rnd.next(1, 3);
            for (int c = 0; c < copies; ++c) {
                addEdge(edges, u, v, randomHeight(heightMode, i * 3 + c));
            }
        }
    }

    if (edges.empty()) {
        addEdge(edges, 1, 2, randomHeight(heightMode, 0));
    }
    shuffle(edges.begin(), edges.end());
    if ((int)edges.size() > 80) edges.resize(80);

    int t = rnd.next(3, 20);
    vector<pair<int, int>> queries;
    int repeatedSource = rnd.next(1, n);
    for (int i = 0; i < t; ++i) {
        int s;
        if (i < t / 3) s = repeatedSource;
        else s = rnd.next(1, n);
        int e = rnd.next(1, n - 1);
        if (e >= s) ++e;
        queries.push_back({s, e});
    }

    println(n, (int)edges.size(), t);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.h);
    }
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
