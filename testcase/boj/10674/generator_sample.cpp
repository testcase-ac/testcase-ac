#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
    int d;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b,
                    int c, int d) {
    if (a > b) swap(a, b);
    if (a == b || !used.insert({a, b}).second) return;
    edges.push_back({a, b, c, d});
}

static void addRandomEdges(vector<Edge>& edges, set<pair<int, int>>& used, int n,
                           int target) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto [a, b] : candidates) {
        if ((int)edges.size() >= target) break;
        int style = rnd.next(0, 5);
        int c = rnd.next(1, 100);
        int d = rnd.next(1, 100);
        if (style == 0) d = c;
        if (style == 1) d = min(100, c + rnd.next(1, 12));
        if (style == 2) c = min(100, d + rnd.next(1, 12));
        addEdge(edges, used, a, b, c, d);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 16);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int limit = rnd.next(0, n - 1);
        for (int i = 1; i <= limit; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 100), rnd.next(1, 100));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        int x = rnd.next(2, n - 1);
        int t1 = rnd.next(1, 50);
        int t2 = rnd.next(1, 50);
        addEdge(edges, used, 1, x, t1, rnd.next(1, 100));
        addEdge(edges, used, x, n, t2, rnd.next(1, 100));
        addEdge(edges, used, 1, n, rnd.next(1, 100), t1 + t2);
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        int middle = rnd.next(2, n - 1);
        for (int v = 2; v <= middle; ++v) {
            addEdge(edges, used, 1, v, rnd.next(1, 35), rnd.next(1, 35));
            addEdge(edges, used, v, n, rnd.next(1, 35), rnd.next(1, 35));
        }
    } else {
        n = rnd.next(8, 16);
    }

    int maxM = n * (n - 1) / 2;
    int target = (int)edges.size();
    if (mode == 4) {
        target = rnd.next(max(0, maxM / 3), maxM);
    } else {
        target = rnd.next(target, min(maxM, target + rnd.next(0, n + 4)));
    }
    addRandomEdges(edges, used, n, target);

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c, edge.d);
    }

    return 0;
}
