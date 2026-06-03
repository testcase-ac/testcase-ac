#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(vector<pair<int, int>>& edges, set<pair<int, int>>& used, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    if (used.insert({a, b}).second) {
        edges.push_back({a, b});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, used, v - 1, v);
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, used, 1, v);
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, used, rnd.next(1, v - 1), v);
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maxExtra = min<int>(candidates.size(), mode == 4 ? 28 : 12);
    int extra = 0;
    if (maxExtra > 0) {
        extra = mode == 0 ? rnd.next(0, min(maxExtra, 2)) : rnd.next(0, maxExtra);
    }
    for (int i = 0; i < extra; ++i) {
        addEdge(edges, used, candidates[i].first, candidates[i].second);
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    int m = edges.size();
    int q = rnd.next(1, m);
    vector<int> query;
    if (rnd.next(0, 1)) {
        for (int i = 1; i <= m && (int)query.size() < q; ++i) {
            query.push_back(i);
        }
    } else {
        vector<int> order(m);
        for (int i = 0; i < m; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin(), order.end());
        query.assign(order.begin(), order.begin() + q);
    }

    println(n, m, q);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    for (int index : query) {
        println(index);
    }

    return 0;
}
