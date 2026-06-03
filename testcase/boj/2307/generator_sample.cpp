#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int t;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int t) {
    if (a > b) swap(a, b);
    if (a == b || !used.insert({a, b}).second) return;
    edges.push_back({a, b, t});
}

static void fillRandomEdges(vector<Edge>& edges, set<pair<int, int>>& used, int n, int targetM, int minT, int maxT) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto [a, b] : candidates) {
        if ((int)edges.size() >= targetM) break;
        addEdge(edges, used, a, b, rnd.next(minT, maxT));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(6, 14);
    int maxM = n * (n - 1) / 2;
    int targetM = rnd.next(6, min(maxM, rnd.next(8, 24)));

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        int heavy = rnd.next(20, 80);
        for (int i = 1; i < n; ++i) addEdge(edges, used, i, i + 1, rnd.next(1, 9));
        for (int i = 2; i + 2 <= n; ++i) {
            if (rnd.next(2)) addEdge(edges, used, i, i + 2, heavy + rnd.next(0, 20));
        }
    } else if (mode == 1) {
        int mid = rnd.next(3, n - 2);
        addEdge(edges, used, 1, 2, rnd.next(1, 5));
        addEdge(edges, used, 2, mid, rnd.next(1, 5));
        addEdge(edges, used, mid, n - 1, rnd.next(1, 5));
        addEdge(edges, used, n - 1, n, rnd.next(1, 5));
        addEdge(edges, used, 1, 3, rnd.next(4, 15));
        addEdge(edges, used, 3, n, rnd.next(4, 15));
        for (int v = 4; v <= n - 2; ++v) addEdge(edges, used, v, rnd.next(1, v - 1), rnd.next(2, 30));
    } else if (mode == 2) {
        vector<int> order;
        for (int i = 1; i <= n; ++i) order.push_back(i);
        shuffle(order.begin() + 1, order.end() - 1);
        for (int i = 0; i + 1 < n; ++i) addEdge(edges, used, order[i], order[i + 1], rnd.next(1, 40));
    } else {
        int hub = rnd.next(2, n - 1);
        addEdge(edges, used, 1, hub, rnd.next(1, 10));
        addEdge(edges, used, hub, n, rnd.next(1, 10));
        for (int v = 2; v < n; ++v) {
            if (v != hub) addEdge(edges, used, v, hub, rnd.next(1, 20));
        }
        addEdge(edges, used, 1, n, rnd.next(30, 120));
    }

    targetM = max(targetM, 6);
    fillRandomEdges(edges, used, n, targetM, 1, 100);
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const Edge& e : edges) println(e.a, e.b, e.t);

    return 0;
}
