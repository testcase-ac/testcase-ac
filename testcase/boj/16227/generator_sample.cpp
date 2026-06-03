#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int t;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, int t) {
    if (u > v) swap(u, v);
    if (used.insert({u, v}).second) {
        edges.push_back({u, v, t});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = 0;
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(0, 2);
        int target = n + 1;
        addEdge(edges, used, 0, target, rnd.next(1, 100));
        for (int v = 1; v <= n; ++v) {
            addEdge(edges, used, 0, v, rnd.next(1, 100));
            addEdge(edges, used, v, target, rnd.next(1, 100));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 9);
        int target = n + 1;
        for (int i = 0; i < target; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(55, 100));
        }
        for (int i = 0; i + 2 <= target; ++i) {
            addEdge(edges, used, i, i + 2, rnd.next(101, 180));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 10);
        int target = n + 1;
        int mid = rnd.next(2, n - 2);
        for (int i = 0; i < mid; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(45, 65));
        }
        for (int i = mid; i < target; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(85, 100));
        }
        for (int i = 0; i + 3 <= target; i += 2) {
            addEdge(edges, used, i, i + 3, rnd.next(95, 100));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 12);
        int target = n + 1;
        int split = rnd.next(2, n - 3);
        addEdge(edges, used, 0, 1, rnd.next(1, 30));
        for (int i = 1; i <= split; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(70, 100));
        }
        addEdge(edges, used, split + 1, target, rnd.next(1, 30));
        addEdge(edges, used, 0, split + 2, rnd.next(95, 100));
        for (int i = split + 2; i < target; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(35, 60));
        }
    } else {
        n = rnd.next(8, 14);
        int target = n + 1;
        for (int i = 0; i < target; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(35, 100));
        }
        int extra = rnd.next(n, 2 * n);
        for (int it = 0; it < extra; ++it) {
            int u = rnd.next(0, target);
            int v = rnd.next(0, target);
            if (u == v) continue;
            int t = rnd.next(4) == 0 ? rnd.next(101, 1000) : rnd.next(1, 100);
            addEdge(edges, used, u, v, t);
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.t);
    }

    return 0;
}
