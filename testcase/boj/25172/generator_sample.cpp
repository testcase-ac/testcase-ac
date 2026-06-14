#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& used, int u, int v) {
    if (u > v) swap(u, v);
    if (u != v) used.insert({u, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? rnd.next(1, 3) : rnd.next(2, 12));
    set<pair<int, int>> used;

    if (mode == 1) {
        for (int i = 1; i < n; ++i) addEdge(used, i, i + 1);
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) addEdge(used, center, i);
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) addEdge(used, i, i + 1);
        if (n >= 3) addEdge(used, n, 1);
        int extra = rnd.next(0, min(4, n));
        for (int i = 0; i < extra; ++i) {
            addEdge(used, rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 4) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) addEdge(used, i, i + 1);
        for (int i = split + 1; i < n; ++i) addEdge(used, i, i + 1);
        if (rnd.next(0, 1) && split >= 2) addEdge(used, 1, split);
        if (rnd.next(0, 1) && n - split >= 2) addEdge(used, split + 1, n);
    } else if (mode == 5) {
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                candidates.push_back({i, j});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int maxEdges = (int)candidates.size();
        int m = rnd.next(n - 1, min(maxEdges, n + 8));
        for (int i = 0; i < m; ++i) used.insert(candidates[i]);
    }

    vector<int> label(n);
    for (int i = 0; i < n; ++i) label[i] = i + 1;
    shuffle(label.begin(), label.end());

    vector<pair<int, int>> edges;
    for (auto [u, v] : used) {
        u = label[u - 1];
        v = label[v - 1];
        if (rnd.next(0, 1)) swap(u, v);
        edges.push_back({u, v});
    }
    shuffle(edges.begin(), edges.end());

    vector<int> removed = label;
    if (rnd.next(0, 1)) {
        shuffle(removed.begin(), removed.end());
    } else {
        reverse(removed.begin(), removed.end());
    }

    println(n, (int)edges.size());
    for (auto [u, v] : edges) println(u, v);
    for (int vertex : removed) println(vertex);

    return 0;
}
