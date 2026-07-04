#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(set<Edge>& edges, int u, int v) {
    if (u > v) swap(u, v);
    edges.insert({u, v});
}

vector<Edge> pathGraph(int n) {
    set<Edge> edges;
    for (int i = 1; i < n; ++i) {
        addEdge(edges, i, i + 1);
    }
    return vector<Edge>(edges.begin(), edges.end());
}

vector<Edge> cycleGraph(int n) {
    set<Edge> edges;
    for (int i = 1; i <= n; ++i) {
        addEdge(edges, i, i == n ? 1 : i + 1);
    }
    return vector<Edge>(edges.begin(), edges.end());
}

vector<Edge> bipartiteGraph(int leftSize, int rightSize) {
    set<Edge> edges;
    int n = leftSize + rightSize;

    int firstRight = leftSize + 1;
    for (int l = 1; l <= leftSize; ++l) {
        addEdge(edges, l, firstRight);
    }
    for (int r = firstRight + 1; r <= n; ++r) {
        addEdge(edges, 1, r);
    }

    int extraBudget = rnd.next(0, min(20, leftSize * rightSize));
    vector<Edge> candidates;
    for (int l = 1; l <= leftSize; ++l) {
        for (int r = leftSize + 1; r <= n; ++r) {
            candidates.push_back({l, r});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (int i = 0; i < extraBudget && i < int(candidates.size()); ++i) {
        addEdge(edges, candidates[i].first, candidates[i].second);
    }
    return vector<Edge>(edges.begin(), edges.end());
}

vector<Edge> denseConnectedGraph(int n) {
    set<Edge> edges;
    for (int i = 1; i < n; ++i) {
        addEdge(edges, i, i + 1);
    }

    vector<Edge> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int target = rnd.next(n - 1, min<int>(1000, candidates.size()));
    for (Edge edge : candidates) {
        if (int(edges.size()) >= target) break;
        addEdge(edges, edge.first, edge.second);
    }
    return vector<Edge>(edges.begin(), edges.end());
}

vector<Edge> starWithCycle(int n, bool oddCycle) {
    set<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        addEdge(edges, 1, i);
    }

    int cycleLen = oddCycle ? 3 : 4;
    if (n >= cycleLen + 1) {
        for (int i = 2; i < 2 + cycleLen; ++i) {
            addEdge(edges, i, i + 1 == 2 + cycleLen ? 2 : i + 1);
        }
    }
    return vector<Edge>(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasetCount = rnd.next(6, 12);
    for (int tc = 0; tc < datasetCount; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(2, 18);
        vector<Edge> edges;

        if (mode == 0) {
            edges = pathGraph(n);
        } else if (mode == 1) {
            n = rnd.next(3, 17);
            edges = cycleGraph(n);
        } else if (mode == 2) {
            int leftSize = rnd.next(1, 8);
            int rightSize = rnd.next(1, 8);
            n = leftSize + rightSize;
            edges = bipartiteGraph(leftSize, rightSize);
        } else if (mode == 3) {
            n = rnd.next(4, 16);
            edges = starWithCycle(n, rnd.next(0, 1) == 1);
        } else {
            n = rnd.next(3, 14);
            edges = denseConnectedGraph(n);
        }

        shuffle(edges.begin(), edges.end());
        println(n, int(edges.size()));
        for (Edge edge : edges) {
            println(edge.first, edge.second);
        }
    }

    println(0, 0);
    return 0;
}
