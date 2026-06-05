#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

void addEdge(vector<tuple<int, int, int>>& edges, int u, int v, int w) {
    edges.emplace_back(u, v, w);
}

int nextWeight(int mode) {
    if (mode == 0) return rnd.next(1, 9);
    if (mode == 1) return rnd.next(1, 20000);
    if (mode == 2) return rnd.next(15000, 20000);
    return rnd.any(vector<int>{1, 2, 3, 19997, 19999, 20000});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 18);
    int weightMode = rnd.next(0, 3);
    vector<tuple<int, int, int>> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, nextWeight(weightMode));
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) addEdge(edges, center, v, nextWeight(weightMode));
        }
    } else if (mode == 2) {
        int spine = rnd.next(3, n);
        for (int i = 1; i < spine; ++i) {
            addEdge(edges, i, i + 1, nextWeight(weightMode));
        }
        for (int v = spine + 1; v <= n; ++v) {
            int parent = rnd.next(1, spine);
            addEdge(edges, parent, v, nextWeight(weightMode));
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            int parent = max(1, v / 2);
            addEdge(edges, parent, v, nextWeight(weightMode));
        }
    } else if (mode == 4) {
        vector<int> component(n + 1);
        iota(component.begin(), component.end(), 0);
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.emplace_back(u, v);
            }
        }
        shuffle(candidates.begin(), candidates.end());

        auto findRoot = [&](int x) {
            while (component[x] != x) x = component[x];
            return x;
        };

        for (auto [u, v] : candidates) {
            int ru = findRoot(u);
            int rv = findRoot(v);
            if (ru == rv) continue;
            component[rv] = ru;
            addEdge(edges, u, v, nextWeight(weightMode));
            if ((int)edges.size() == n - 1) break;
        }
    } else {
        int armA = rnd.next(1, n - 2);
        int armB = rnd.next(armA + 1, n - 1);
        for (int v = 2; v <= armA; ++v) {
            addEdge(edges, v - 1, v, nextWeight(weightMode));
        }
        addEdge(edges, 1, armA + 1, nextWeight(weightMode));
        for (int v = armA + 2; v <= armB + 1; ++v) {
            addEdge(edges, v - 1, v, nextWeight(weightMode));
        }
        for (int v = armB + 2; v <= n; ++v) {
            int parent = rnd.next(1, armB + 1);
            addEdge(edges, parent, v, nextWeight(weightMode));
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n);
    for (auto [u, v, w] : edges) {
        if (rnd.next(0, 1)) swap(u, v);
        println(u, v, w);
    }

    return 0;
}
