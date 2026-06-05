#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int t;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 2 ? 12 : 10);

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int u, int v) {
        if (u > v) {
            swap(u, v);
        }
        if (used.insert({u, v}).second) {
            edges.push_back({u, v});
        }
    };

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(vertices[i - 1], vertices[i]);
        }
    } else if (mode == 1) {
        int center = vertices[0];
        for (int i = 1; i < n; ++i) {
            addEdge(center, vertices[i]);
        }
    } else {
        for (int i = 1; i < n; ++i) {
            int parent = rnd.next(0, i - 1);
            addEdge(vertices[parent], vertices[i]);
        }
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v})) {
                candidates.push_back({u, v});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maxEdges = n * (n - 1) / 2;
    int target = static_cast<int>(edges.size());
    if (mode == 2) {
        target = rnd.next(n - 1, maxEdges);
    } else if (mode == 3) {
        target = min(maxEdges, n - 1 + rnd.next(1, min<int>(candidates.size(), n)));
    } else if (mode >= 4) {
        target = min(maxEdges, n - 1 + rnd.next(0, min<int>(candidates.size(), 3)));
    }

    while (static_cast<int>(edges.size()) < target) {
        addEdge(candidates.back().first, candidates.back().second);
        candidates.pop_back();
    }

    vector<int> days;
    int base = (mode == 4 ? rnd.next(2, 20) : 1);
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        int step = (mode == 5 && i > 0 ? rnd.next(2, 5) : 1);
        if (i == 0) {
            days.push_back(base);
        } else {
            days.push_back(days.back() + step);
        }
    }
    shuffle(days.begin(), days.end());

    vector<Edge> output;
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        auto [u, v] = edges[i];
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        output.push_back({u, v, days[i]});
    }
    shuffle(output.begin(), output.end());

    println(n, static_cast<int>(output.size()));
    for (const Edge& edge : output) {
        println(edge.u, edge.v, edge.t);
    }

    return 0;
}
