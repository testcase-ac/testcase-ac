#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(vector<pair<int, int>>& edges, set<pair<int, int>>& used, int u,
                    int v) {
    if (u == v) return;
    auto key = minmax(u, v);
    if (used.insert(key).second) edges.push_back({u, v});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) addEdge(edges, used, i, i + 1);
    } else if (mode == 2) {
        for (int start = 1; start <= n;) {
            int len = min(n - start + 1, rnd.next(1, 4));
            int center = start;
            for (int v = start + 1; v < start + len; ++v) {
                addEdge(edges, used, center, v);
            }
            start += len;
        }
    } else {
        double density = rnd.next(0.0, 0.45);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) addEdge(edges, used, i, j);
            }
        }
    }

    if (mode == 4) {
        int extra = rnd.next(0, min(12, n * (n - 1) / 2));
        for (int tries = 0; tries < 4 * extra && static_cast<int>(edges.size()) < extra;
             ++tries) {
            addEdge(edges, used, rnd.next(1, n), rnd.next(1, n));
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    vector<int> schedule(n);
    if (rnd.next(0, 2) == 0) {
        for (int i = 0; i < n; ++i) schedule[i] = i + 1;
        shuffle(schedule.begin(), schedule.end());
    } else {
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) schedule[i] = rnd.next(lo, hi);
    }

    println(n, static_cast<int>(edges.size()));
    for (auto edge : edges) println(edge.first, edge.second);
    println(schedule);

    return 0;
}
