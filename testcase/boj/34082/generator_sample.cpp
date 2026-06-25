#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 24);
    vector<pair<int, int>> edges;

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
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) {
            edges.push_back({v - 1, v});
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
            int parent = rnd.next(1, v - 1);
            edges.push_back({parent, v});
        }
    }

    vector<int> labels(n);
    for (int i = 0; i < n; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());

    for (auto& edge : edges) {
        edge.first = labels[edge.first - 1];
        edge.second = labels[edge.second - 1];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> modChoices = {
        2,
        3,
        4,
        6,
        7,
        10,
        97,
        1000,
        1000000000,
    };
    int m = rnd.next(0, 3) == 0 ? rnd.any(modChoices) : rnd.next(2, 1000000000);

    println(n, m);
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
