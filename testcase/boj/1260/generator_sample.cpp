#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Edge = pair<int, int>;

static void addEdge(vector<Edge>& edges, int u, int v) {
    edges.push_back({u, v});
}

static void addRandomEdges(vector<Edge>& edges, int n, int count, bool allowLoops) {
    for (int i = 0; i < count; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (!allowLoops) {
            while (v == u) {
                v = rnd.next(1, n);
            }
        }
        addEdge(edges, u, v);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    int v = rnd.next(1, n);
    vector<Edge> edges;

    if (mode == 0) {
        // Sparse path with random labels and a few extra cross edges.
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            p[i] = i + 1;
        }
        shuffle(p.begin(), p.end());
        for (int i = 1; i < n; ++i) {
            addEdge(edges, p[i - 1], p[i]);
        }
        addRandomEdges(edges, n, rnd.next(0, n / 2), false);
    } else if (mode == 1) {
        // Star and tail cases make DFS ordering sensitive to vertex numbers.
        int center = rnd.next(1, n);
        for (int u = 1; u <= n; ++u) {
            if (u != center) {
                addEdge(edges, center, u);
            }
        }
        int tail = rnd.next(1, n);
        for (int i = 0; i < rnd.next(1, n); ++i) {
            int to = rnd.next(1, n);
            if (to != tail) {
                addEdge(edges, tail, to);
                tail = to;
            }
        }
    } else if (mode == 2) {
        // Disconnected graph where the start component may be small.
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) {
            addEdge(edges, i, i + 1);
        }
        for (int i = split + 1; i < n; ++i) {
            addEdge(edges, i, i + 1);
        }
        addRandomEdges(edges, n, rnd.next(1, n), false);
    } else if (mode == 3) {
        // Duplicate-heavy multigraph, valid under the statement and validator.
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (a == b) {
            b = (a % n) + 1;
        }
        int repeats = rnd.next(n, min(10000, n * 3));
        for (int i = 0; i < repeats; ++i) {
            addEdge(edges, a, b);
        }
        addRandomEdges(edges, n, rnd.next(1, n), false);
    } else if (mode == 4) {
        // Loop-heavy cases check that self edges do not create extra visits.
        int loops = rnd.next(1, n);
        for (int i = 0; i < loops; ++i) {
            int u = rnd.next(1, n);
            addEdge(edges, u, u);
        }
        addRandomEdges(edges, n, rnd.next(1, n * 2), true);
    } else {
        // Moderately dense simple graph with randomized orientation.
        vector<Edge> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                candidates.push_back({i, j});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int take = rnd.next(n - 1, min<int>(candidates.size(), n * 3));
        for (int i = 0; i < take; ++i) {
            Edge e = candidates[i];
            if (rnd.next(0, 1)) {
                swap(e.first, e.second);
            }
            edges.push_back(e);
        }
    }

    if (edges.empty()) {
        addEdge(edges, 1, min(2, n));
    }

    shuffle(edges.begin(), edges.end());
    if ((int)edges.size() > 10000) {
        edges.resize(10000);
    }

    println(n, (int)edges.size(), v);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
