#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 15);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int v = 1; v < n; ++v) {
            edges.push_back({v, v + 1});
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.push_back({center, v});
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int v = 1; v < spine; ++v) {
            edges.push_back({v, v + 1});
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.push_back({rnd.next(1, spine), v});
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v / 2, v});
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({rnd.next(1, v - 1), v});
        }
    }

    vector<int> label(n + 1);
    for (int v = 1; v <= n; ++v) {
        label[v] = v;
    }
    shuffle(label.begin() + 1, label.end());

    vector<vector<int>> graph(n + 1);
    for (auto [a, b] : edges) {
        int u = label[a];
        int v = label[b];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());
    for (int v = 1; v <= n; ++v) {
        shuffle(graph[v].begin(), graph[v].end());
    }

    int root = rnd.next(1, n);

    cout << n << '\n';
    for (int v : order) {
        cout << v;
        for (int to : graph[v]) {
            cout << ' ' << to;
        }
        cout << " -1\n";
    }
    cout << root << '\n';

    return 0;
}
