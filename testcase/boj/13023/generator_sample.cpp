#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(set<pair<int, int>>& used, int a, int b) {
    if (a > b) swap(a, b);
    used.insert({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 14);
    int mode = rnd.next(5);
    set<pair<int, int>> used;

    if (mode == 0) {
        vector<int> path(n);
        for (int i = 0; i < n; ++i) path[i] = i;
        shuffle(path.begin(), path.end());
        for (int i = 0; i < 4; ++i) addEdge(used, path[i], path[i + 1]);

        int extra = rnd.next(0, min(8, n * (n - 1) / 2 - 4));
        while ((int)used.size() < 4 + extra) {
            int a = rnd.next(n);
            int b = rnd.next(n);
            if (a != b) addEdge(used, a, b);
        }
    } else if (mode == 1) {
        int center = rnd.next(n);
        for (int v = 0; v < n; ++v) {
            if (v != center && rnd.next(2)) addEdge(used, center, v);
        }
        if (used.empty()) addEdge(used, center, (center + 1) % n);
    } else if (mode == 2) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        int pathLen = rnd.next(1, 3);
        for (int i = 0; i < pathLen; ++i) addEdge(used, order[i], order[i + 1]);
        int hub = order[rnd.next(pathLen + 1)];
        for (int i = pathLen + 1; i < n; ++i) {
            if (rnd.next(3) != 0) addEdge(used, hub, order[i]);
        }
    } else if (mode == 3) {
        vector<int> cycle(n);
        for (int i = 0; i < n; ++i) cycle[i] = i;
        shuffle(cycle.begin(), cycle.end());

        int len = rnd.next(5, n);
        for (int i = 0; i < len; ++i) addEdge(used, cycle[i], cycle[(i + 1) % len]);
    } else {
        double density = rnd.next(0.05, 0.35);
        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                if (rnd.next() < density) addEdge(used, a, b);
            }
        }
        if (used.empty()) {
            int a = rnd.next(n);
            int b = rnd.next(n - 1);
            if (b >= a) ++b;
            addEdge(used, a, b);
        }
    }

    vector<int> label(n);
    for (int i = 0; i < n; ++i) label[i] = i;
    shuffle(label.begin(), label.end());

    vector<pair<int, int>> edges;
    for (auto [a, b] : used) {
        a = label[a];
        b = label[b];
        if (rnd.next(2)) swap(a, b);
        edges.push_back({a, b});
    }
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (auto [a, b] : edges) println(a, b);
}
