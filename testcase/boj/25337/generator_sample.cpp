#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int color;
};

vector<pair<int, int>> makeTree(int n, int mode) {
    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({1, i});
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i});
        }
    }
    return edges;
}

vector<int> makeValues(int n, int mode) {
    vector<int> values(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            values[i] = rnd.next(-5, 5);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            values[i] = rnd.any(vector<int>{-1000, -1, 0, 1, 1000});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            values[i] = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 20);
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int treeMode = rnd.next(0, 3);
    int colorMode = rnd.next(0, 4);

    vector<pair<int, int>> baseEdges = makeTree(n, treeMode);
    vector<Edge> edges;
    for (int i = 0; i < static_cast<int>(baseEdges.size()); ++i) {
        int color;
        if (colorMode == 0) {
            color = 1;
        } else if (colorMode == 1) {
            color = i + 1;
        } else if (colorMode == 2) {
            color = (i % 2) + 1;
        } else if (colorMode == 3) {
            color = rnd.next(1, min(5, n));
        } else {
            color = rnd.any(vector<int>{1, 2, 3, 199999, 200000});
        }
        edges.push_back({baseEdges[i].first, baseEdges[i].second, color});
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());

    for (Edge& edge : edges) {
        edge.u = labels[edge.u - 1];
        edge.v = labels[edge.v - 1];
        if (rnd.next(0, 1) == 1) {
            swap(edge.u, edge.v);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> a = makeValues(n, rnd.next(0, 2));
    vector<int> b = makeValues(n, rnd.next(0, 2));

    println(n);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.color);
    }
    println(a);
    println(b);

    return 0;
}
