#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int mode = rnd.next(5);
    int maxWeight = rnd.next(1, 25);

    vector<pair<int, int>> edges;
    for (int v = 1; v < n; ++v) {
        int parent = 0;
        if (mode == 0) {
            parent = v - 1;
        } else if (mode == 1) {
            parent = 0;
        } else if (mode == 2) {
            parent = (v - 1) / 2;
        } else if (mode == 3) {
            parent = rnd.next(0, v - 1);
        } else {
            parent = rnd.next(max(0, v - 3), v - 1);
        }
        edges.push_back({parent, v});
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());

    vector<vector<pair<int, int>>> tree(n);
    for (auto [u, v] : edges) {
        int w = rnd.next(1, maxWeight);
        int a = perm[u];
        int b = perm[v];
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }

    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int root = 0; root < n; ++root) {
        vector<int> parent(n, -1);
        vector<int> stack = {root};
        parent[root] = root;

        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();

            for (auto [to, w] : tree[v]) {
                if (parent[to] != -1) {
                    continue;
                }
                parent[to] = v;
                dist[root][to] = dist[root][v] + w;
                stack.push_back(to);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(dist[i]);
    }

    return 0;
}
