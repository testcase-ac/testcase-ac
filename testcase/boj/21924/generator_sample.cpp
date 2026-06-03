#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 12);
    int mode = rnd.next(0, 4);
    vector<Edge> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int u, int v, int w) {
        if (u == v) return false;
        if (rnd.next(0, 1)) swap(u, v);
        pair<int, int> key = minmax(u, v);
        if (!used.insert(key).second) return false;
        edges.push_back({u, v, w});
        return true;
    };

    auto cost = [&](bool high) {
        if (high) return rnd.next(999990, 1000000);
        int style = rnd.next(0, 3);
        if (style == 0) return rnd.next(1, 9);
        if (style == 1) return rnd.next(10, 100);
        if (style == 2) return rnd.next(1, 3) * rnd.next(1000, 20000);
        return rnd.next(1, 1000000);
    };

    if (mode == 0 || mode == 1 || mode == 3) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());

        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(order[i], parent, cost(mode == 3));
        }

        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (!used.count({u, v})) candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int extraLimit = mode == 0 ? min<int>(3, candidates.size())
                                   : min<int>(n + 4, candidates.size());
        int extra = rnd.next(0, extraLimit);
        for (int i = 0; i < extra; ++i) {
            addEdge(candidates[i].first, candidates[i].second, cost(mode == 3));
        }
    } else {
        n = max(n, 4);
        vector<int> labels(n);
        for (int i = 0; i < n; ++i) labels[i] = i + 1;
        shuffle(labels.begin(), labels.end());

        int leftSize = rnd.next(2, n - 2);
        vector<int> left(labels.begin(), labels.begin() + leftSize);
        vector<int> right(labels.begin() + leftSize, labels.end());

        auto addComponentEdges = [&](const vector<int>& component) {
            for (int i = 1; i < (int)component.size(); ++i) {
                addEdge(component[i], component[rnd.next(0, i - 1)], cost(false));
            }
            vector<pair<int, int>> candidates;
            for (int i = 0; i < (int)component.size(); ++i) {
                for (int j = i + 1; j < (int)component.size(); ++j) {
                    pair<int, int> key = minmax(component[i], component[j]);
                    if (!used.count(key)) candidates.push_back(key);
                }
            }
            shuffle(candidates.begin(), candidates.end());
            int extra = candidates.empty() ? 0 : rnd.next(0, min<int>(2, candidates.size()));
            for (int i = 0; i < extra; ++i) {
                addEdge(candidates[i].first, candidates[i].second, cost(false));
            }
        };

        addComponentEdges(left);
        addComponentEdges(right);
    }

    if (mode == 4) {
        for (auto& edge : edges) {
            edge.w = rnd.next(0, 1) ? 1 : rnd.next(2, 6);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const auto& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
