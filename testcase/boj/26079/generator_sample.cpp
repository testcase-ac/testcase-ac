#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        for (int i = 1; i < n; ++i) {
            edges.push_back({i, i + 1});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        int root = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != root) {
                edges.push_back({root, v});
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 15);
        int split = rnd.next(2, n - 1);
        for (int i = 1; i < split; ++i) {
            edges.push_back({i, i + 1});
        }
        for (int i = split; i < n; ++i) {
            edges.push_back({i, i + 1});
        }
    } else {
        n = (mode == 6 ? rnd.next(30, 80) : rnd.next(5, 18));
        double parentProb = rnd.next(0.25, 0.95);
        for (int v = 2; v <= n; ++v) {
            if (rnd.next() < parentProb) {
                int parent;
                if (mode == 4) {
                    parent = rnd.next(1, v - 1);
                } else {
                    parent = max(1, v - rnd.next(1, min(v - 1, 5)));
                }
                edges.push_back({parent, v});
            }
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (auto [a, b] : edges) {
        println(label[a], label[b]);
    }

    return 0;
}
