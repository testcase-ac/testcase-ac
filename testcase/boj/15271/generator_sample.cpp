#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& edges, int u, int v) {
    if (u == v) return;
    if (u > v) swap(u, v);
    edges.insert({u, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 60);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 2) {
        int oddCount = rnd.next(1, 8);
        int evenCount = rnd.next(1, 8);
        n = 2 * max(oddCount, evenCount);
        vector<int> odds, evens;
        for (int i = 1; i <= n; ++i) {
            if (i % 2) odds.push_back(i);
            else evens.push_back(i);
        }
        shuffle(odds.begin(), odds.end());
        shuffle(evens.begin(), evens.end());
        odds.resize(oddCount);
        evens.resize(evenCount);
        for (int u : odds) {
            for (int v : evens) addEdge(edges, u, v);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 40);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i + 1 < n; i += 2) addEdge(edges, vertices[i], vertices[i + 1]);

        int extra = rnd.next(0, min(30, n * (n - 1) / 2));
        for (int i = 0; i < extra; ++i) addEdge(edges, rnd.next(1, n), rnd.next(1, n));
    } else if (mode == 4) {
        n = rnd.next(6, 28);
        double probability = rnd.next(0.05, 0.45);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < probability) addEdge(edges, u, v);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(8, 24);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if ((u % 2) != (v % 2) || rnd.next(0, 3) == 0) addEdge(edges, u, v);
            }
        }
    } else {
        n = rnd.next(80, 200);
        int target = rnd.next(0, min(500, n * (n - 1) / 2));
        while ((int)edges.size() < target) addEdge(edges, rnd.next(1, n), rnd.next(1, n));
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());
    for (auto& edge : output) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    println(n, (int)output.size());
    for (const auto& edge : output) println(edge.first, edge.second);

    return 0;
}
