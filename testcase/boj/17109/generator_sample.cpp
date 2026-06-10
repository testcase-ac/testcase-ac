#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class DisjointSet {
public:
    explicit DisjointSet(int n) : parent_(n + 1), rank_(n + 1, 0) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int x) {
        if (parent_[x] == x) {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        if (rank_[a] < rank_[b]) {
            swap(a, b);
        }
        parent_[b] = a;
        if (rank_[a] == rank_[b]) {
            ++rank_[a];
        }
        return true;
    }

private:
    vector<int> parent_;
    vector<int> rank_;
};

static void addEdge(set<pair<int, int>>& used, vector<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    if (used.insert({a, b}).second) {
        edges.push_back({a, b});
    }
}

static vector<pair<int, int>> allMissingEdges(int n, const set<pair<int, int>>& used) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());
    return candidates;
}

static void relabelAndOrient(int n, vector<pair<int, int>>& edges) {
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = 1;
    set<pair<int, int>> used;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        for (int v = 2; v <= n; ++v) {
            addEdge(used, edges, v - 1, v);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        for (int v = 2; v <= n; ++v) {
            addEdge(used, edges, 1, v);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        for (int v = 1; v <= n; ++v) {
            addEdge(used, edges, v, v == n ? 1 : v + 1);
        }
        auto candidates = allMissingEdges(n, used);
        int extraCount = rnd.next(0, min<int>(candidates.size(), n / 2));
        for (int i = 0; i < extraCount; ++i) {
            addEdge(used, edges, candidates[i].first, candidates[i].second);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 13);
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                addEdge(used, edges, a, b);
            }
        }
    } else {
        n = rnd.next(4, 16);
        DisjointSet dsu(n);
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (auto [a, b] : candidates) {
            if (dsu.unite(a, b)) {
                addEdge(used, edges, a, b);
            }
        }

        candidates = allMissingEdges(n, used);
        int maxExtra = min<int>(candidates.size(), mode == 5 ? n : 2 * n);
        int extraCount = rnd.next(0, maxExtra);
        for (int i = 0; i < extraCount; ++i) {
            addEdge(used, edges, candidates[i].first, candidates[i].second);
        }
    }

    relabelAndOrient(n, edges);

    println(n, static_cast<int>(edges.size()));
    for (auto [a, b] : edges) {
        println(a, b);
    }

    return 0;
}
