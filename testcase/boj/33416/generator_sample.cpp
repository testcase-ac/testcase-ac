#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(vector<pair<int, int>>& edges, int u, int v) {
    edges.push_back({u, v});
}

static void maybeShuffleLabels(int n, vector<pair<int, int>>& edges) {
    if (n <= 2 || rnd.next(2) == 0) {
        return;
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);

    vector<int> rest;
    for (int i = 2; i <= n; ++i) {
        rest.push_back(i);
    }
    shuffle(rest.begin(), rest.end());
    for (int i = 2; i <= n; ++i) {
        label[i] = rest[i - 2];
    }

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = rnd.next(1, 30);
    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 2 || mode == 4) {
        n = rnd.next(3, 30);
    }

    vector<pair<int, int>> edges;

    if (n == 1) {
        println(n);
        return 0;
    }

    if (mode == 0) {
        addEdge(edges, 1, 2);
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1);
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            addEdge(edges, 1, i);
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            addEdge(edges, i, i + 1);
        }
        for (int i = spine + 1; i <= n; ++i) {
            int attach = rnd.next(1, spine);
            addEdge(edges, attach, i);
        }
    } else if (mode == 4) {
        int branches = rnd.next(2, min(n - 1, 6));
        int nextVertex = 2;
        vector<int> tips;
        for (int b = 0; b < branches; ++b) {
            addEdge(edges, 1, nextVertex);
            tips.push_back(nextVertex);
            ++nextVertex;
        }
        while (nextVertex <= n) {
            int& tip = tips[rnd.next(static_cast<int>(tips.size()))];
            addEdge(edges, tip, nextVertex);
            tip = nextVertex;
            ++nextVertex;
        }
    } else if (mode == 5) {
        for (int i = 2; i <= n; ++i) {
            int parent = max(1, i / 2);
            addEdge(edges, parent, i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            addEdge(edges, parent, i);
        }
    }

    maybeShuffleLabels(n, edges);
    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
