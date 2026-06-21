#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int c;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& usedEdges,
                    set<int>& usedColors, int u, int v, int c) {
    if (u == v || usedEdges.count({u, v}) || usedColors.count(c)) {
        return;
    }
    usedEdges.insert({u, v});
    usedColors.insert(c);
    edges.push_back({u, v, c});
}

static int nextColor(set<int>& usedColors, int lo, int hi) {
    int c = rnd.next(lo, hi);
    while (usedColors.count(c)) {
        c = rnd.next(lo, hi);
    }
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);
    int s = rnd.next(1, n);
    int t = rnd.next(1, n - 1);
    if (t >= s) {
        ++t;
    }

    vector<Edge> edges;
    set<pair<int, int>> usedEdges;
    set<int> usedColors;

    auto addRandomEdge = [&](int colorLo, int colorHi) {
        for (int tries = 0; tries < 100; ++tries) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            if (u == v || usedEdges.count({u, v})) {
                continue;
            }
            addEdge(edges, usedEdges, usedColors, u, v,
                    nextColor(usedColors, colorLo, colorHi));
            return;
        }
    };

    if (mode == 0) {
        // Unreachable T: generate edges only among vertices except T.
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && u != t && v != t) {
                    candidates.push_back({u, v});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int extra = rnd.next(0, min(12, (int)candidates.size()));
        for (int i = 0; i < extra; ++i) {
            int u = candidates[i].first;
            int v = candidates[i].second;
            addEdge(edges, usedEdges, usedColors, u, v,
                    nextColor(usedColors, 1, 1000));
        }
    } else if (mode == 1) {
        // A short S-to-T path with distracting larger-color alternatives.
        vector<int> path = {s};
        vector<int> mids;
        for (int v = 1; v <= n; ++v) {
            if (v != s && v != t) {
                mids.push_back(v);
            }
        }
        shuffle(mids.begin(), mids.end());
        int len = rnd.next(1, min(5, n - 1));
        for (int i = 0; i + 1 < len && i < (int)mids.size(); ++i) {
            path.push_back(mids[i]);
        }
        path.push_back(t);

        int color = rnd.next(1, 20);
        for (int i = 0; i + 1 < (int)path.size(); ++i) {
            addEdge(edges, usedEdges, usedColors, path[i], path[i + 1], color);
            color += rnd.next(1, 7);
        }
        int extra = rnd.next(0, 10);
        for (int i = 0; i < extra; ++i) {
            addRandomEdge(100, 10000);
        }
    } else if (mode == 2) {
        // Reachable cycle before T, useful for lexicographic infinite-repeat cases.
        if (n < 3) {
            n = 3;
            s = 1;
            t = 3;
        }
        int a = s;
        vector<int> choices;
        for (int v = 1; v <= n; ++v) {
            if (v != a && v != t) {
                choices.push_back(v);
            }
        }
        int b = rnd.any(choices);
        addEdge(edges, usedEdges, usedColors, a, b, 1);
        addEdge(edges, usedEdges, usedColors, b, a, 2);
        addEdge(edges, usedEdges, usedColors, b, t, rnd.next(20, 40));
        addEdge(edges, usedEdges, usedColors, a, t, rnd.next(41, 80));
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            addRandomEdge(100, 10000);
        }
    } else if (mode == 3) {
        // Dense small reachable graph with random ordering and colors.
        addEdge(edges, usedEdges, usedColors, s, t, rnd.next(30, 60));
        int backbone = rnd.next(1, min(4, n - 1));
        int cur = s;
        for (int i = 0; i < backbone; ++i) {
            int nxt = (i + 1 == backbone) ? t : rnd.next(1, n);
            if (nxt == cur) {
                nxt = nxt % n + 1;
            }
            addEdge(edges, usedEdges, usedColors, cur, nxt,
                    nextColor(usedColors, 1, 1000));
            cur = nxt;
        }
        int extra = rnd.next(0, min(18, n * (n - 1)));
        for (int i = 0; i < extra; ++i) {
            addRandomEdge(1, 100000);
        }
    } else {
        // Minimum-size and near-empty cases.
        n = rnd.next(2, 4);
        s = 1;
        t = n;
        if (rnd.next(0, 1)) {
            addEdge(edges, usedEdges, usedColors, s, t, 1000000000);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), s, t);
    for (const Edge& e : edges) {
        println(e.u, e.v, e.c);
    }

    return 0;
}
