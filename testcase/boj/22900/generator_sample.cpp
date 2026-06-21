#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

long long randomWeight(int mode) {
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(1, 20);
    if (mode == 2) return rnd.next(999999980, 1000000000);
    if (mode == 3) return rnd.any(vector<long long>{1, 2, 3, 7, 42, 999999937, 1000000000});
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 0 ? 1 : rnd.next(2, 14);
    vector<pair<int, int>> edges;

    if (mode == 1) {
        for (int v = 2; v <= n; ++v) edges.push_back({v - 1, v});
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) edges.push_back({center, v});
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) edges.push_back({v - 1, v});
        for (int v = spine + 1; v <= n; ++v) edges.push_back({rnd.next(1, spine), v});
    } else if (mode == 4) {
        for (int v = 2; v <= n; ++v) edges.push_back({v / 2, v});
    } else if (mode == 5) {
        for (int v = 2; v <= n; ++v) edges.push_back({rnd.next(1, v - 1), v});
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    int weightMode = rnd.next(0, 4);
    println(n);
    shuffle(edges.begin(), edges.end());
    for (auto [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(0, 1)) swap(u, v);
        println(u, v, randomWeight(weightMode));
    }

    return 0;
}
