#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

void addEdge(set<pair<int, int>>& used, vector<pair<int, int>>& edges, int u, int v) {
    if (u != v && used.insert({u, v}).second) {
        edges.push_back({u, v});
    }
}

void addRandomEdges(int n, int target, set<pair<int, int>>& used, vector<pair<int, int>>& edges) {
    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (u != v && !used.count({u, v})) {
                candidates.push_back({u, v});
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());
    target = min(target, static_cast<int>(candidates.size()));
    for (int i = 0; i < target; ++i) {
        addEdge(used, edges, candidates[i].first, candidates[i].second);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    int a = rnd.next(1, 8);
    int b = rnd.next(1, 20);
    int c = rnd.next(1, 100);

    if (mode == 0) {
        n = rnd.next(2, 8);
        a = b = c = rnd.next(1, 100);
        addRandomEdges(n, rnd.next(0, min(5, n * (n - 1))), used, edges);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        for (int i = 1; i < n; ++i) {
            addEdge(used, edges, i, i + 1);
        }
        a = rnd.next(1, min(100, n + 3));
        b = rnd.next(1, min(100, n + 3));
        c = rnd.next(1, min(100, n + 3));
        addRandomEdges(n, rnd.next(0, n), used, edges);
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        for (int i = 1; i <= n; ++i) {
            addEdge(used, edges, i, i % n + 1);
        }
        a = rnd.next(1, 100);
        b = rnd.next(1, 100);
        c = rnd.next(1, 100);
        addRandomEdges(n, rnd.next(0, n), used, edges);
    } else if (mode == 3) {
        n = rnd.next(5, 12);
        int split = rnd.next(2, n - 2);
        for (int v = 2; v <= split; ++v) {
            addEdge(used, edges, 1, v);
        }
        for (int u = 2; u <= split; ++u) {
            for (int v = split + 1; v <= n; ++v) {
                if (rnd.next(0, 1)) {
                    addEdge(used, edges, u, v);
                }
            }
        }
        for (int u = split + 1; u < n; ++u) {
            addEdge(used, edges, u, n);
        }
        a = 1;
        b = rnd.next(2, 5);
        c = rnd.next(2, 8);
        addRandomEdges(n, rnd.next(0, n), used, edges);
    } else if (mode == 4) {
        n = rnd.next(4, 12);
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (u != v && rnd.next(0, 99) < rnd.next(25, 80)) {
                    addEdge(used, edges, u, v);
                }
            }
        }
    } else {
        n = rnd.next(2, 10);
        int pathLen = rnd.next(1, n - 1);
        for (int i = 1; i <= pathLen; ++i) {
            addEdge(used, edges, i, i + 1);
        }
        for (int u = pathLen + 2; u <= n; ++u) {
            addEdge(used, edges, u, rnd.next(1, n - 1));
        }
        a = pathLen;
        b = rnd.next(1, 100);
        c = rnd.next(1, 100);
        addRandomEdges(n, rnd.next(0, n), used, edges);
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), a, b, c);
    for (const auto& [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
