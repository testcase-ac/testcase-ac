#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(4, 12);
    set<pair<int, int>> edgeSet;

    auto addEdge = [&](int u, int v) {
        if (u != v) edgeSet.insert({u, v});
    };

    vector<int> vertices;
    for (int i = 1; i <= n; ++i) vertices.push_back(i);
    shuffle(vertices.begin(), vertices.end());

    int a = vertices[0];
    int b = vertices[1];
    int c = vertices[2];
    int meet = vertices[3];

    if (mode == 0) {
        addEdge(a, meet);
        addEdge(b, meet);
        addEdge(c, meet);
        for (int i = 4; i < n; ++i) {
            if (rnd.next(0, 1)) addEdge(vertices[i], meet);
            if (rnd.next(0, 1)) addEdge(meet, vertices[i]);
        }
    } else if (mode == 1) {
        addEdge(meet, a);
        addEdge(meet, b);
        addEdge(meet, c);
        for (int i = 4; i < n; ++i) {
            int u = vertices[i];
            addEdge(u, rnd.any(vector<int>{a, b, c}));
        }
    } else if (mode == 2) {
        vector<int> cycle = {a, b, c, meet};
        for (int i = 4; i < n && (int)cycle.size() < rnd.next(4, min(n, 8)); ++i) {
            cycle.push_back(vertices[i]);
        }
        for (int i = 0; i < (int)cycle.size(); ++i) {
            addEdge(cycle[i], cycle[(i + 1) % cycle.size()]);
        }
        for (int i = 0; i < (int)cycle.size(); ++i) {
            if (rnd.next(0, 2) == 0) addEdge(cycle[i], meet);
        }
    } else if (mode == 3) {
        double probability = rnd.next(0.08, 0.28);
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next() < probability) addEdge(u, v);
            }
        }
    } else if (mode == 4) {
        double probability = rnd.next(0.35, 0.75);
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next() < probability) addEdge(u, v);
            }
        }
    } else {
        int x = vertices[4 % n];
        int y = vertices[5 % n];
        addEdge(a, x);
        addEdge(b, x);
        addEdge(c, y);
        addEdge(x, y);
        addEdge(y, meet);
        if (rnd.next(0, 1)) addEdge(c, c == x ? meet : x);
        for (int i = 6; i < n; ++i) {
            addEdge(vertices[i - 1], vertices[i]);
            if (rnd.next(0, 1)) addEdge(vertices[i], meet);
        }
    }

    while (edgeSet.empty()) {
        addEdge(a, meet);
    }

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    println(a, b, c);
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
