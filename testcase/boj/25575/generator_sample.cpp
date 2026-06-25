#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, set<Edge>& used, int x, int y) {
    if (used.emplace(x, y).second) {
        edges.emplace_back(x, y);
    }
}

vector<Edge> allEdges(int n, int m) {
    vector<Edge> edges;
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            edges.emplace_back(x, y);
        }
    }
    return edges;
}

vector<Edge> makeCase(int n, int m, int mode) {
    vector<Edge> edges;
    set<Edge> used;

    if (mode == 0) {
        addEdge(edges, used, rnd.next(1, n), rnd.next(1, m));
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int y = 1; y <= m; ++y) {
            if (rnd.next(0, 1)) {
                addEdge(edges, used, center, y);
            }
        }
    } else if (mode == 2) {
        int center = rnd.next(1, m);
        for (int x = 1; x <= n; ++x) {
            if (rnd.next(0, 1)) {
                addEdge(edges, used, x, center);
            }
        }
    } else if (mode == 3) {
        for (int x = 1; x <= n; ++x) {
            addEdge(edges, used, x, rnd.next(1, m));
        }
        for (int y = 1; y <= m; ++y) {
            addEdge(edges, used, rnd.next(1, n), y);
        }
    } else if (mode == 4) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, m);
        for (int x = 1; x <= a; ++x) {
            for (int y = 1; y <= b; ++y) {
                addEdge(edges, used, x, y);
            }
        }
    } else {
        vector<Edge> candidates = allEdges(n, m);
        shuffle(candidates.begin(), candidates.end());
        int maxK = min<int>(candidates.size(), rnd.next(1, min<int>(candidates.size(), 30)));
        int k = rnd.next(1, maxK);
        edges.assign(candidates.begin(), candidates.begin() + k);
    }

    if (edges.empty()) {
        addEdge(edges, used, rnd.next(1, n), rnd.next(1, m));
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 12);
        int m = rnd.next(1, 12);

        if (mode == 4) {
            n = rnd.next(2, 8);
            m = rnd.next(2, 8);
        }

        vector<Edge> edges = makeCase(n, m, mode);
        println(n, m, static_cast<int>(edges.size()));
        for (const auto& edge : edges) {
            println(edge.first, edge.second);
        }
    }

    return 0;
}
