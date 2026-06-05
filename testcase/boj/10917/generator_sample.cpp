#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 30));
    vector<pair<int, int>> edges;

    if (mode == 0) {
        // Single dream state: start and target are already the same situation.
    } else if (mode == 1) {
        // Sparse unreachable graph: no transition reaches N from 1.
        int m = rnd.next(0, min(20, n * (n - 1) / 2));
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(1, max(1, n - 1));
            int y = rnd.next(x + 1, n);
            if (x == 1 || y == n) {
                x = rnd.next(2, max(2, n - 1));
                if (x >= n) break;
                y = rnd.next(x + 1, n);
                if (y == n && rnd.next(0, 1)) y = x + 1;
            }
            if (x < y && x != 1 && y != n) edges.push_back({x, y});
        }
    } else if (mode == 2) {
        // Long path from 1 to N, with distracting forward edges.
        for (int i = 1; i < n; ++i) edges.push_back({i, i + 1});
        int extra = rnd.next(0, min(25, n * (n - 1) / 2));
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(1, n - 1);
            int y = rnd.next(x + 1, n);
            edges.push_back({x, y});
        }
    } else if (mode == 3) {
        // Direct shortcut plus noise, useful for solutions that mishandle early exits.
        edges.push_back({1, n});
        int extra = rnd.next(0, min(35, n * (n - 1) / 2));
        for (int i = 0; i < extra; ++i) {
            int x = rnd.next(1, n - 1);
            int y = rnd.next(x + 1, n);
            edges.push_back({x, y});
        }
    } else if (mode == 4) {
        // Layered DAG with many equivalent shortest paths.
        vector<int> layer;
        for (int v = 2; v < n; ++v)
            if (rnd.next(0, 1)) layer.push_back(v);
        if (layer.empty() && n > 2) layer.push_back(rnd.next(2, n - 1));
        if (layer.empty()) {
            edges.push_back({1, n});
        } else {
            for (int v : layer) {
                edges.push_back({1, v});
                edges.push_back({v, n});
            }
        }
        for (int a : layer)
            for (int b : layer)
                if (a < b && rnd.next(0, 2) == 0) edges.push_back({a, b});
    } else {
        // Random compact DAG; duplicates are sometimes preserved intentionally.
        double density = rnd.next(0.05, 0.35);
        for (int x = 1; x <= n; ++x)
            for (int y = x + 1; y <= n; ++y)
                if (rnd.next() < density) edges.push_back({x, y});
    }

    if (!edges.empty() && rnd.next(0, 3) == 0) {
        int copies = rnd.next(1, min(5, (int)edges.size()));
        for (int i = 0; i < copies; ++i) edges.push_back(rnd.any(edges));
    }

    shuffle(edges.begin(), edges.end());
    if ((int)edges.size() > 80) edges.resize(80);

    println(n, (int)edges.size());
    for (auto edge : edges) println(edge.first, edge.second);

    return 0;
}
