#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Monster {
    int a;
    int x;
    int y;
    int c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int t = rnd.next(1, 20);

    if (mode == 0) {
        n = rnd.next(2, 8);
        t = rnd.next(1, min(10, n + 2));
    } else if (mode == 5) {
        n = rnd.next(2, 6);
        t = rnd.next(80, 100);
    }

    vector<Monster> monsters(n + 1);
    for (int i = 1; i <= n; ++i) {
        int profile = rnd.next(0, 4);
        if (mode == 5 && i == 1) {
            monsters[i] = {rnd.next(900000000, 1000000000), rnd.next(9000, 10000),
                           rnd.next(1, 5), rnd.next(1, 10000)};
        } else if (profile == 0) {
            monsters[i] = {rnd.next(1, 20), rnd.next(1, 10), rnd.next(1, 10), rnd.next(1, 20)};
        } else if (profile == 1) {
            monsters[i] = {rnd.next(1, 100), rnd.next(1, 5), rnd.next(20, 100), rnd.next(1, 50)};
        } else if (profile == 2) {
            monsters[i] = {rnd.next(100, 10000), rnd.next(100, 10000), rnd.next(1, 100), rnd.next(1, 10000)};
        } else {
            monsters[i] = {rnd.next(1, 1000), rnd.next(1, 1000), rnd.next(1, 1000), rnd.next(1, 1000)};
        }
    }

    set<pair<int, int>> used;
    vector<pair<int, int>> edges;
    auto addEdge = [&](int u, int v) {
        if (u == v) return;
        if (used.insert({u, v}).second) edges.push_back({u, v});
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) addEdge(i, i % n + 1);
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) addEdge(rnd.next(1, v - 1), v);
        for (int tries = 0; tries < n; ++tries) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) addEdge(1, v);
        for (int v = 2; v <= n; ++v)
            if (rnd.next(0, 1)) addEdge(v, rnd.next(1, n));
    } else if (mode == 4) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next(0, 99) < 35) addEdge(u, v);
            }
        }
    } else {
        addEdge(1, 2);
        for (int i = 2; i < n; ++i) {
            if (rnd.next(0, 2) != 0) addEdge(i, i + 1);
            if (rnd.next(0, 1)) addEdge(i + 1, 1);
        }
    }

    if (edges.empty()) addEdge(1, 2);
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), t);
    for (int i = 1; i <= n; ++i) {
        println(monsters[i].a, monsters[i].x, monsters[i].y, monsters[i].c);
    }
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
