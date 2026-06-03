#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(vector<pair<int, int>>& edges, int u, int v) {
    if (rnd.next(2)) swap(u, v);
    edges.push_back({u, v});
}

static vector<pair<int, int>> shuffledDistinctEdges(int v) {
    vector<pair<int, int>> candidates;
    for (int i = 1; i <= v; ++i) {
        for (int j = i + 1; j <= v; ++j) {
            candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    return candidates;
}

static vector<pair<int, int>> makeRandomGraph(int v, bool forceOddCycle) {
    vector<pair<int, int>> edges;

    if (forceOddCycle) {
        int len = rnd.next(3, min(v, 9));
        if (len % 2 == 0) --len;
        vector<int> cycle;
        for (int i = 1; i <= v; ++i) cycle.push_back(i);
        shuffle(cycle.begin(), cycle.end());
        cycle.resize(len);
        for (int i = 0; i < len; ++i) {
            addEdge(edges, cycle[i], cycle[(i + 1) % len]);
        }
    }

    vector<pair<int, int>> candidates = shuffledDistinctEdges(v);
    int target = rnd.next(max(1, v - 1), min<int>(candidates.size(), v * 2));
    for (auto [u, w] : candidates) {
        if ((int)edges.size() >= target) break;
        addEdge(edges, u, w);
    }

    shuffle(edges.begin(), edges.end());
    return edges;
}

static vector<pair<int, int>> makeBipartiteGraph(int v) {
    vector<int> left, right;
    for (int i = 1; i <= v; ++i) {
        if (rnd.next(2)) {
            left.push_back(i);
        } else {
            right.push_back(i);
        }
    }
    if (left.empty()) {
        left.push_back(right.back());
        right.pop_back();
    }
    if (right.empty()) {
        right.push_back(left.back());
        left.pop_back();
    }

    vector<pair<int, int>> candidates;
    for (int u : left) {
        for (int w : right) {
            candidates.push_back({u, w});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int target = rnd.next(1, min<int>(candidates.size(), max(1, v * 2)));
    vector<pair<int, int>> edges;
    for (int i = 0; i < target; ++i) {
        addEdge(edges, candidates[i].first, candidates[i].second);
    }
    return edges;
}

static vector<pair<int, int>> makeDuplicateCase(int v) {
    vector<pair<int, int>> base = makeBipartiteGraph(v);
    vector<pair<int, int>> edges = base;
    int extra = rnd.next(1, max(1, v));
    for (int i = 0; i < extra; ++i) {
        auto edge = rnd.any(base);
        addEdge(edges, edge.first, edge.second);
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(2, 5);
    println(k);

    for (int tc = 0; tc < k; ++tc) {
        int mode = (tc == 0) ? 0 : rnd.next(4);
        int v = rnd.next(2, 12);

        vector<pair<int, int>> edges;
        if (mode == 0) {
            edges = makeBipartiteGraph(v);
        } else if (mode == 1) {
            v = max(v, 3);
            edges = makeRandomGraph(v, true);
        } else if (mode == 2) {
            edges = makeDuplicateCase(v);
        } else {
            edges = makeRandomGraph(v, false);
        }

        println(v, (int)edges.size());
        for (auto [u, w] : edges) {
            println(u, w);
        }
    }

    return 0;
}
