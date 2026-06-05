#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;

    auto addEdge = [&](int u, int v) {
        if (u != v) edges.push_back({u, v});
    };

    if (mode == 0) {
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < 30) addEdge(u, v);
            }
        }
    } else if (mode == 1) {
        int cycle = rnd.next(2, min(n, 8));
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());

        for (int i = 0; i < cycle; ++i) {
            addEdge(vertices[i], vertices[(i + 1) % cycle]);
        }
        for (int i = cycle; i < n; ++i) {
            int to = vertices[rnd.next(0, i - 1)];
            addEdge(vertices[i], to);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int u = 1; u <= split; ++u) {
            addEdge(u, rnd.next(split + 1, n));
        }
        for (int u = split + 1; u <= n; ++u) {
            int count = rnd.next(0, min(3, n - 1));
            for (int j = 0; j < count; ++j) {
                int v = rnd.next(1, n);
                if (v != u) addEdge(u, v);
            }
        }
    } else if (mode == 3) {
        int cycleStart = rnd.next(1, n - 1);
        for (int i = 1; i < cycleStart; ++i) addEdge(i, i + 1);
        for (int i = cycleStart; i < n; ++i) addEdge(i, i + 1);
        addEdge(n, cycleStart);
    } else if (mode == 4) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next(0, 99) < 45) addEdge(u, v);
            }
        }
    } else {
        int base = rnd.next(1, n - 1);
        int target = rnd.next(base + 1, n);
        int repeats = rnd.next(2, 8);
        for (int i = 0; i < repeats; ++i) addEdge(base, target);
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 99) < 50) addEdge(i, i + 1);
        }
    }

    if (edges.empty()) {
        addEdge(1, 2);
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
