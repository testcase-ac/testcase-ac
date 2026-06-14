#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a == b) return;
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

void addRandomEdges(set<pair<int, int>>& edges, int n, int target) {
    vector<pair<int, int>> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (!edges.count({i, j})) candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto edge : candidates) {
        if ((int)edges.size() >= target) break;
        edges.insert(edge);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(2, 14);
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 9);
    } else if (mode == 1) {
        n = rnd.next(3, 14);
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) addEdge(edges, center, i);
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        for (int i = 1; i <= n; ++i) addEdge(edges, i, i % n + 1);
        addRandomEdges(edges, n, rnd.next((int)edges.size(), min(5000, n * (n - 1) / 2)));
    } else if (mode == 4) {
        n = 2 * rnd.next(1, 7);
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());
        for (int i = 0; i < n; i += 2) addEdge(edges, p[i], p[i + 1]);
        addRandomEdges(edges, n, rnd.next((int)edges.size(), min(5000, n * (n - 1) / 2)));
    } else if (mode == 5) {
        n = rnd.next(4, 14);
        double density = rnd.next(0.15, 0.9);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) addEdge(edges, i, j);
            }
        }
    } else if (mode == 6) {
        n = rnd.next(8, 14);
        int target = rnd.next(n - 1, min(5000, n * (n - 1) / 2));
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
        addRandomEdges(edges, n, target);
    } else {
        n = 1000;
        addRandomEdges(edges, n, rnd.next(4900, 5000));
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());

    println(n, (int)output.size());
    for (auto edge : output) println(edge.first, edge.second);

    return 0;
}
