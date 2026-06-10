#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& used, vector<pair<int, int>>& edges, int a, int b) {
    if (a != b && used.insert({a, b}).second) {
        edges.push_back({a, b});
    }
}

static void addRandomEdges(int n, int target, set<pair<int, int>>& used, vector<pair<int, int>>& edges) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            if (a != b && !used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());
    for (auto edge : candidates) {
        if ((int)edges.size() >= target) {
            break;
        }
        addEdge(used, edges, edge.first, edge.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    int c = rnd.next(1, 12);

    vector<int> moonies(n);
    moonies[0] = 0;
    int maxMooney = rnd.next(0, 1000);
    for (int i = 1; i < n; ++i) {
        moonies[i] = rnd.next(0, maxMooney);
    }

    set<pair<int, int>> used;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        addEdge(used, edges, 1, rnd.next(2, n));
    } else if (mode == 1) {
        int cycleLen = rnd.next(2, min(n, 8));
        for (int i = 1; i < cycleLen; ++i) {
            addEdge(used, edges, i, i + 1);
        }
        addEdge(used, edges, cycleLen, 1);
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            addEdge(used, edges, i, i + 1);
        }
        addEdge(used, edges, n, rnd.next(1, n - 1));
        addEdge(used, edges, rnd.next(2, n), 1);
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            addEdge(used, edges, 1, i);
            if (rnd.next(2) == 0) {
                addEdge(used, edges, i, 1);
            }
        }
    } else {
        int cycleLen = rnd.next(2, min(n, 6));
        for (int i = 1; i < cycleLen; ++i) {
            addEdge(used, edges, i, i + 1);
        }
        addEdge(used, edges, cycleLen, 1);
        for (int i = cycleLen + 1; i <= n; ++i) {
            addEdge(used, edges, rnd.next(1, i - 1), i);
            if (rnd.next(3) == 0) {
                addEdge(used, edges, i, rnd.next(1, i - 1));
            }
        }
    }

    int maxEdges = min(2000, n * (n - 1));
    int targetEdges = rnd.next(max(1, (int)edges.size()), min(maxEdges, max(1, (int)edges.size() + rnd.next(0, n))));
    addRandomEdges(n, targetEdges, used, edges);
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), c);
    println(moonies);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
