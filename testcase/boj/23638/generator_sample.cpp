#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 30);
    int cycleSize;
    if (mode == 0) {
        cycleSize = 3;
    } else if (mode == 1) {
        cycleSize = n;
    } else if (mode == 2) {
        cycleSize = rnd.next(3, min(n, 6));
    } else if (mode == 3) {
        cycleSize = rnd.next(max(3, n / 2), n);
    } else {
        cycleSize = rnd.next(3, n);
    }

    vector<pair<int, int>> edges;
    vector<int> parent(n + 1, 0);
    vector<int> depth(n + 1, 0);
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b) {
        if (a > b) {
            swap(a, b);
        }
        if (used.insert({a, b}).second) {
            edges.push_back({a, b});
        }
    };

    for (int i = 1; i <= cycleSize; ++i) {
        int j = (i == cycleSize ? 1 : i + 1);
        addEdge(i, j);
    }

    for (int v = cycleSize + 1; v <= n; ++v) {
        int attach;
        if (mode == 0) {
            attach = rnd.next(1, v - 1);
        } else if (mode == 2) {
            attach = v - 1;
        } else if (mode == 4 && rnd.next(0, 1) == 0) {
            attach = rnd.next(1, cycleSize);
        } else {
            int bestDepth = -1;
            attach = 1;
            for (int candidate = 1; candidate < v; ++candidate) {
                if (depth[candidate] > bestDepth && rnd.next(0, 2) != 0) {
                    bestDepth = depth[candidate];
                    attach = candidate;
                }
            }
        }
        parent[v] = attach;
        depth[v] = depth[attach] + 1;
        addEdge(attach, v);
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    vector<pair<int, int>> relabeled;
    for (auto [u, v] : edges) {
        int a = label[u];
        int b = label[v];
        if (a > b) {
            swap(a, b);
        }
        relabeled.push_back({a, b});
    }
    shuffle(relabeled.begin(), relabeled.end());

    println(n);
    for (auto [u, v] : relabeled) {
        println(u, v);
    }

    return 0;
}
