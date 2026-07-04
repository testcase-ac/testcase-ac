#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    int k = rnd.next(2, min(8, n + 2));

    vector<int> color(n + 1);
    color[1] = rnd.next(1, k);
    color[2] = rnd.next(1, k - 1);
    if (color[2] >= color[1]) {
        ++color[2];
    }
    for (int i = 3; i <= n; ++i) {
        color[i] = rnd.next(1, k);
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (color[u] != color[v]) {
                candidates.push_back({u, v});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    vector<pair<int, int>> edges;
    if (mode == 0) {
        int m = rnd.next(1, min<int>(candidates.size(), max(1, n - 1)));
        edges.assign(candidates.begin(), candidates.begin() + m);
    } else if (mode == 1) {
        for (int u = 1; u < n; ++u) {
            if (color[u] != color[u + 1]) {
                edges.push_back({u, u + 1});
            }
        }
        if (edges.empty()) {
            edges.push_back(candidates[0]);
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v == center || color[v] == color[center]) {
                continue;
            }
            edges.push_back({min(center, v), max(center, v)});
        }
        if (edges.empty()) {
            edges.push_back(candidates[0]);
        }
    } else if (mode == 3) {
        int cap = rnd.next(1, min<int>(candidates.size(), 35));
        edges.assign(candidates.begin(), candidates.begin() + cap);
    } else {
        for (auto edge : candidates) {
            if (rnd.next(0, 99) < rnd.next(20, 75)) {
                edges.push_back(edge);
            }
        }
        if (edges.empty()) {
            edges.push_back(candidates[0]);
        }
    }

    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());

    println(n, static_cast<int>(edges.size()), k);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << color[i];
    }
    cout << '\n';
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
