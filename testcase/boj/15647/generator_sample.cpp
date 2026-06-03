#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int pickWeight(int mode) {
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return 5;
    }
    return rnd.next(1, 5);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 30);
    vector<pair<int, int>> edges;

    if (n == 1) {
        println(n);
        return 0;
    }

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v});
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.push_back({center, v});
            }
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v / 2, v});
        }
    } else if (mode == 3) {
        int handle = rnd.next(1, n);
        for (int v = 2; v <= handle; ++v) {
            edges.push_back({v - 1, v});
        }
        for (int v = handle + 1; v <= n; ++v) {
            edges.push_back({handle, v});
        }
    } else if (mode == 4) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({rnd.next(1, v - 1), v});
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int parent = max(1, v - rnd.next(1, min(v - 1, 4)));
            edges.push_back({parent, v});
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    int weightMode = rnd.next(3);
    println(n);
    for (auto [u, v] : edges) {
        if (rnd.next(2) == 0) {
            swap(u, v);
        }
        println(label[u], label[v], pickWeight(weightMode));
    }

    return 0;
}
