#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int u, int v) {
        if (u == v) return;
        if (used.insert({u, v}).second) edges.push_back({u, v});
    };

    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < rnd.next(20, 80)) addEdge(u, v);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        int pairs = rnd.next(1, min(10, n * (n - 1) / 2));
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u)
            for (int v = u + 1; v <= n; ++v)
                candidates.push_back({u, v});
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < pairs; ++i) {
            addEdge(candidates[i].first, candidates[i].second);
            addEdge(candidates[i].second, candidates[i].first);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        int cycleLen = rnd.next(3, n);
        vector<int> vertices;
        for (int i = 1; i <= n; ++i) vertices.push_back(i);
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < cycleLen; ++i) {
            addEdge(vertices[i], vertices[(i + 1) % cycleLen]);
        }
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(u, v);
        }
    } else {
        n = rnd.next(4, 14);
        int target = rnd.next(n, min(60, n * (n - 1)));
        while ((int)edges.size() < target) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(u, v);
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto edge : edges) println(edge.first, edge.second);

    return 0;
}
