#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    bool forced;
};

static bool addEdge(vector<Edge>& edges, set<pair<int, int>>& used,
                    set<int>& forcedStarts, int from, int to, bool forced) {
    if (from == to || used.count({from, to})) return false;
    if (forced && forcedStarts.count(from)) return false;

    used.insert({from, to});
    if (forced) forcedStarts.insert(from);
    edges.push_back({from, to, forced});
    return true;
}

static void addRandomEdges(vector<Edge>& edges, set<pair<int, int>>& used,
                           set<int>& forcedStarts, int n, int target) {
    int attempts = 0;
    while (static_cast<int>(edges.size()) < target && attempts < target * 80 + 200) {
        ++attempts;
        int from = rnd.next(1, n);
        int to = rnd.next(1, n);
        if (from == to || used.count({from, to})) continue;

        bool canForce = !forcedStarts.count(from);
        bool forced = canForce && rnd.next(0, 99) < 35;
        addEdge(edges, used, forcedStarts, from, to, forced);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 28);
    vector<Edge> edges;
    set<pair<int, int>> used;
    set<int> forcedStarts;

    if (mode == 0) {
        n = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        int cycleLen = rnd.next(2, n);
        vector<int> nodes;
        for (int i = 1; i <= cycleLen; ++i) nodes.push_back(i);
        shuffle(nodes.begin(), nodes.end());
        for (int i = 0; i < cycleLen; ++i) {
            addEdge(edges, used, forcedStarts, nodes[i], nodes[(i + 1) % cycleLen], true);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 24);
        for (int i = 1; i < n; ++i) {
            bool forced = rnd.next(0, 99) < 60;
            addEdge(edges, used, forcedStarts, i, i + 1, forced);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        int center = rnd.next(1, n);
        for (int node = 1; node <= n; ++node) {
            if (node == center) continue;
            addEdge(edges, used, forcedStarts, center, node, false);
            if (rnd.next(0, 99) < 45) {
                addEdge(edges, used, forcedStarts, node, center, rnd.next(0, 99) < 50);
            }
        }
    } else {
        n = rnd.next(8, 30);
        for (int i = 1; i <= n; ++i) {
            int to = i == n ? 1 : i + 1;
            addEdge(edges, used, forcedStarts, i, to, rnd.next(0, 99) < 70);
        }
    }

    int maxEdges = n * (n - 1);
    int target = rnd.next(static_cast<int>(edges.size()), min(maxEdges, n * 3));
    addRandomEdges(edges, used, forcedStarts, n, target);
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.forced ? -edge.from : edge.from, edge.to);
    }

    return 0;
}
