#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? rnd.next(1, 3) : rnd.next(2, 14));

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<long long> heights(n + 1);
    long long base = rnd.next(1, 1000000000 - 3 * n);
    for (int rank = 0; rank < n; ++rank) {
        heights[order[rank]] = base + 3LL * rank + rnd.next(0, 1);
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    set<pair<int, int>> edgeSet;
    auto addEdge = [&](int a, int b) {
        if (a > b) {
            swap(a, b);
        }
        if (a != b) {
            edgeSet.insert({a, b});
        }
    };

    if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            addEdge(order[i - 1], order[i]);
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center && rnd.next(0, 1)) {
                addEdge(center, v);
            }
        }
    } else if (mode == 3) {
        for (auto edge : candidates) {
            if (rnd.next(0, 3) != 0) {
                edgeSet.insert(edge);
            }
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            addEdge(rnd.next(1, i - 1), i);
        }
        for (auto edge : candidates) {
            if (rnd.next(0, 5) == 0) {
                edgeSet.insert(edge);
            }
        }
    } else if (mode == 5) {
        double density = rnd.next(0.0, 0.55);
        for (auto edge : candidates) {
            if (rnd.next() < density) {
                edgeSet.insert(edge);
            }
        }
    }

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    int k;
    if (mode == 0) {
        k = n;
    } else if (rnd.next(0, 4) == 0) {
        k = 1;
    } else if (rnd.next(0, 3) == 0) {
        k = n;
    } else {
        k = rnd.next(1, n);
    }

    vector<int> open(n);
    iota(open.begin(), open.end(), 1);
    shuffle(open.begin(), open.end());
    open.resize(k);

    println(n, static_cast<int>(edges.size()));
    vector<long long> outputHeights;
    for (int i = 1; i <= n; ++i) {
        outputHeights.push_back(heights[i]);
    }
    println(outputHeights);
    for (auto [u, v] : edges) {
        println(u, v);
    }
    println(k);
    println(open);

    return 0;
}
