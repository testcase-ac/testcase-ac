#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 14);
    int q = rnd.next(1, 16);
    int mode = rnd.next(4);

    int cycleLen;
    if (mode == 0) {
        cycleLen = n;
    } else if (mode == 1) {
        cycleLen = 3;
    } else if (mode == 2) {
        cycleLen = rnd.next(3, min(n, 5));
    } else {
        cycleLen = rnd.next(3, n);
    }

    vector<pair<int, int>> edges;
    for (int i = 1; i <= cycleLen; ++i) {
        int next = (i == cycleLen ? 1 : i + 1);
        edges.emplace_back(i, next);
    }

    for (int v = cycleLen + 1; v <= n; ++v) {
        int parent;
        if (mode == 1) {
            parent = rnd.next(1, cycleLen);
        } else if (mode == 2) {
            parent = v - 1;
        } else {
            parent = rnd.next(1, v - 1);
        }
        edges.emplace_back(parent, v);
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, q);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    for (int i = 0; i < q; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) {
            ++v;
        }
        println(u, v);
    }

    return 0;
}
