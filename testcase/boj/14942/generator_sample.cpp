#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0) ? 1 : rnd.next(2, 14);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v});
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({1, v});
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v / 2, v});
        }
    } else if (mode == 4) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({rnd.next(1, v - 1), v});
        }
    } else {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) {
            edges.push_back({v - 1, v});
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.push_back({rnd.next(1, spine), v});
        }
    }

    vector<int> weight(n + 1, 0);
    for (int i = 0; i < (int)edges.size(); ++i) {
        int w;
        if (i % 5 == 0) {
            w = 1;
        } else if (i % 5 == 1) {
            w = rnd.next(2, 12);
        } else if (i % 5 == 2) {
            w = rnd.next(90, 140);
        } else {
            w = rnd.next(1, 10000);
        }
        weight[i] = w;
    }

    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < (int)edges.size(); ++i) {
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].push_back({b, weight[i]});
        graph[b].push_back({a, weight[i]});
    }

    vector<int> parent(n + 1, 0), edgeToParent(n + 1, 0), order = {1};
    for (int qi = 0; qi < (int)order.size(); ++qi) {
        int u = order[qi];
        for (auto [v, w] : graph[u]) {
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            edgeToParent[v] = w;
            order.push_back(v);
        }
    }

    vector<int> energy(n + 1, 1);
    energy[1] = rnd.next(1, 100000);
    for (int v = 2; v <= n; ++v) {
        vector<int> prefix = {0};
        int sum = 0;
        for (int x = v; x != 1; x = parent[x]) {
            sum += edgeToParent[x];
            prefix.push_back(sum);
        }

        int choice = rnd.next(0, 5);
        if (choice == 0) {
            energy[v] = max(1, edgeToParent[v] - 1);
        } else if (choice == 1) {
            energy[v] = edgeToParent[v];
        } else if (choice == 2) {
            energy[v] = prefix[rnd.next(1, (int)prefix.size() - 1)];
        } else if (choice == 3) {
            energy[v] = min(100000, sum);
        } else if (choice == 4) {
            energy[v] = rnd.next(1, min(100000, max(1, sum + 20)));
        } else {
            energy[v] = rnd.next(1, 100000);
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(edges.begin(), edges.end());
    }

    println(n);
    for (int v = 1; v <= n; ++v) {
        println(energy[v]);
    }
    for (auto [a, b] : edges) {
        int w = 1;
        for (int i = 0; i < (int)graph[a].size(); ++i) {
            if (graph[a][i].first == b) {
                w = graph[a][i].second;
                break;
            }
        }
        println(a, b, w);
    }

    return 0;
}
