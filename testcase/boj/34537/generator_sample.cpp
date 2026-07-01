#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
    int x;
    int y;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int budgetMode = rnd.next(4);
    int b = 0;
    if (budgetMode == 0) {
        b = rnd.next(1, 12);
    } else if (budgetMode == 1) {
        b = rnd.next(13, 120);
    } else if (budgetMode == 2) {
        b = rnd.next(121, 2000);
    } else {
        b = rnd.next(2001, 1000000);
    }

    vector<Edge> edges;
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    auto addEdge = [&](int u, int v) {
        int valueMode = rnd.next(5);
        int w = 0;
        int x = 0;
        int y = 0;
        if (valueMode == 0) {
            w = rnd.next(1, 8);
            x = rnd.next(1, 5);
            y = rnd.next(1, 3);
        } else if (valueMode == 1) {
            w = rnd.next(1, 20);
            x = rnd.next(20, 100);
            y = rnd.next(1, 10);
        } else if (valueMode == 2) {
            w = rnd.next(50, 300);
            x = rnd.next(1, 12);
            y = rnd.next(1, 10);
        } else if (valueMode == 3) {
            w = rnd.next(1, 100000);
            x = rnd.next(1, 100000);
            y = rnd.next(1, 10);
        } else {
            int base = rnd.next(1, 40);
            w = base;
            x = base + rnd.next(0, 20);
            y = rnd.next(1, 10);
        }
        edges.push_back({u, v, w, x, y});
    };

    for (int i = 1; i < n; ++i) {
        int parent = order[rnd.next(i)];
        addEdge(parent, order[i]);
    }

    vector<pair<int, int>> simpleCandidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            simpleCandidates.push_back({u, v});
        }
    }
    shuffle(simpleCandidates.begin(), simpleCandidates.end());

    int candidateCount = static_cast<int>(simpleCandidates.size());
    int mode = rnd.next(4);
    int extra = 0;
    if (mode == 0) {
        extra = rnd.next(0, min(n, candidateCount));
    } else if (mode == 1) {
        int hi = min(3 * n, candidateCount);
        extra = rnd.next(min(n, hi), hi);
    } else if (mode == 2) {
        extra = rnd.next(0, min(8, candidateCount));
    } else {
        extra = rnd.next(min(candidateCount, 2 * n), candidateCount);
    }

    for (int i = 0; i < extra; ++i) {
        addEdge(simpleCandidates[i].first, simpleCandidates[i].second);
    }

    if (mode == 2 || rnd.next(4) == 0) {
        int parallelCount = rnd.next(1, min(8, 100000 - static_cast<int>(edges.size())));
        for (int i = 0; i < parallelCount; ++i) {
            const Edge& e = edges[rnd.next(static_cast<int>(edges.size()))];
            addEdge(e.u, e.v);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), b);
    for (const Edge& e : edges) {
        println(e.u, e.v, e.w, e.x, e.y);
    }

    return 0;
}
