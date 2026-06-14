#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(set<pair<int, int>>& edges, int u, int v) {
    if (u > v) swap(u, v);
    edges.insert({u, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 16);
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 14);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 1) {
        n = rnd.next(3, 16);
        for (int i = 2; i <= n; ++i) addEdge(edges, 1, i);
    } else if (mode == 2) {
        n = rnd.next(4, 16);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
        addEdge(edges, n, 1);
        int chords = rnd.next(0, n / 2);
        for (int i = 0; i < chords; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u != v) addEdge(edges, u, v);
        }
    } else if (mode == 3) {
        int left = rnd.next(1, 7);
        int right = rnd.next(1, 7);
        n = left + right;
        for (int u = 1; u <= left; ++u) {
            for (int v = left + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < 65) addEdge(edges, u, v);
            }
        }
        if (edges.empty()) addEdge(edges, 1, left + 1);
    } else if (mode == 4) {
        n = rnd.next(4, 13);
        int clique = rnd.next(3, n);
        for (int i = 1; i <= clique; ++i) {
            for (int j = i + 1; j <= clique; ++j) addEdge(edges, i, j);
        }
        for (int v = clique + 1; v <= n; ++v) {
            addEdge(edges, v, rnd.next(1, clique));
            if (rnd.next(0, 1)) addEdge(edges, v, rnd.next(1, clique));
        }
    } else if (mode == 5) {
        n = rnd.next(5, 16);
        int handle = rnd.next(2, n - 2);
        for (int i = 1; i < handle; ++i) addEdge(edges, i, i + 1);
        for (int v = handle + 1; v <= n; ++v) addEdge(edges, handle, v);
    } else {
        n = rnd.next(2, 16);
        int possible = n * (n - 1) / 2;
        int target = rnd.next(1, min(possible, 35));
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) candidates.push_back({i, j});
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < target; ++i) edges.insert(candidates[i]);
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) label[i] = i;
    shuffle(label.begin() + 1, label.end());

    vector<pair<int, int>> output;
    for (auto [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(0, 1)) swap(u, v);
        output.push_back({u, v});
    }
    shuffle(output.begin(), output.end());

    println(n, (int)output.size());
    for (auto [u, v] : output) {
        println(u, v);
    }

    return 0;
}
