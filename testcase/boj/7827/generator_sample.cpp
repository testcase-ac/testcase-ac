#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& edges, int a, int b) {
    edges.insert({a, b});
}

void addRandomEdges(set<pair<int, int>>& edges, int n, int target, bool allowSelfLoops) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            if (!allowSelfLoops && a == b) continue;
            if (!edges.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (int i = 0; i < (int)candidates.size() && (int)edges.size() < target; ++i) {
        edges.insert(candidates[i]);
    }
}

set<pair<int, int>> makeCase(int n, int mode) {
    set<pair<int, int>> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
        int target = rnd.next(n - 1, min(n * (n - 1), n + 8));
        addRandomEdges(edges, n, target, false);
    } else if (mode == 1) {
        int cycleSize = rnd.next(2, n);
        for (int i = 1; i <= cycleSize; ++i) {
            addEdge(edges, i, i == cycleSize ? 1 : i + 1);
        }
        for (int i = cycleSize + 1; i <= n; ++i) {
            addEdge(edges, rnd.next(1, i - 1), i);
        }
        int target = rnd.next((int)edges.size(), min(n * n, n + 10));
        addRandomEdges(edges, n, target, true);
    } else if (mode == 2) {
        int selfLoops = rnd.next(1, min(n, 4));
        vector<int> vertices;
        for (int i = 1; i <= n; ++i) vertices.push_back(i);
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < selfLoops; ++i) addEdge(edges, vertices[i], vertices[i]);
        int target = rnd.next(selfLoops, min(n * n, selfLoops + n + 4));
        addRandomEdges(edges, n, target, true);
    } else {
        int target = rnd.next(1, min(n * n, n * 3));
        addRandomEdges(edges, n, target, rnd.next(0, 1) == 1);
    }

    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 3);
        int n = rnd.next(2, 12);
        set<pair<int, int>> edges = makeCase(n, mode);

        println(n, (int)edges.size());
        for (auto edge : edges) {
            println(edge.first, edge.second);
        }
    }

    return 0;
}
