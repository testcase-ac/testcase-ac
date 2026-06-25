#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    if (mode == 1) {
        n = rnd.next(2, 8) * 2;
    } else if (mode == 2) {
        n = rnd.next(3, 13) | 1;
    }

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    int leftSize = 0;
    if (n > 1) {
        if (mode == 3) {
            leftSize = rnd.next(1, n - 1);
        } else if (mode == 4) {
            leftSize = rnd.next(0, 1) ? 1 : n - 1;
        } else {
            int lo = max(1, n / 2 - 2);
            int hi = min(n - 1, n / 2 + 2);
            leftSize = rnd.next(lo, hi);
        }
    }

    vector<int> left(vertices.begin(), vertices.begin() + leftSize);
    vector<int> right(vertices.begin() + leftSize, vertices.end());

    vector<pair<int, int>> candidates;
    for (int u : left) {
        for (int v : right) {
            candidates.emplace_back(u, v);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    double keepProbability = 0.0;
    if (mode == 0) {
        keepProbability = rnd.next(0.0, 0.35);
    } else if (mode == 1) {
        keepProbability = rnd.next(0.55, 1.0);
    } else if (mode == 2) {
        keepProbability = rnd.next(0.15, 0.75);
    } else if (mode == 3) {
        keepProbability = rnd.next(0.0, 1.0);
    } else if (mode == 4) {
        keepProbability = rnd.next(0.45, 1.0);
    } else {
        keepProbability = rnd.next(0.05, 0.55);
    }

    vector<pair<int, int>> edges;
    for (auto edge : candidates) {
        if (rnd.next() < keepProbability) {
            if (rnd.next(0, 1)) {
                swap(edge.first, edge.second);
            }
            edges.push_back(edge);
        }
    }

    if (mode == 5 && !candidates.empty()) {
        int take = rnd.next(1, min<int>(static_cast<int>(candidates.size()), 2 * n));
        edges.assign(candidates.begin(), candidates.begin() + take);
        for (auto& edge : edges) {
            if (rnd.next(0, 1)) {
                swap(edge.first, edge.second);
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
