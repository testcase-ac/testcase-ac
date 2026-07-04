#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int s;
    int t;
    int d;
    int u;
};

static void addEdge(vector<Edge>& edges, vector<vector<bool>>& used, int s, int t, int d, int u) {
    if (s > t) swap(s, t);
    if (s == t || used[s][t]) return;
    used[s][t] = true;
    edges.push_back({s, t, d, u});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<Edge> edges;

    int sunLimit = rnd.next(0, 30);
    if (mode == 0) sunLimit = 0;
    if (mode == 1) sunLimit = rnd.next(1, 5);
    if (mode == 2) sunLimit = rnd.next(20, 120);
    if (mode == 5) sunLimit = 3600;

    if (mode != 4) {
        for (int i = 0; i + 1 < n; ++i) {
            int underground = rnd.next(0, 1);
            int d = rnd.next(1, mode == 5 ? 4000 : 30);
            addEdge(edges, used, i, i + 1, d, underground ? 0 : 1);
        }
    } else {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i + 1 < split; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 20), rnd.next(0, 1));
        }
        for (int i = split; i + 1 < n; ++i) {
            addEdge(edges, used, i, i + 1, rnd.next(1, 20), rnd.next(0, 1));
        }
    }

    if (n >= 3 && mode <= 3) {
        int mid = rnd.next(1, n - 2);
        addEdge(edges, used, 0, mid, rnd.next(1, 20), 0);
        addEdge(edges, used, mid, n - 1, rnd.next(1, 20), 1);
    }

    if (mode == 1) {
        addEdge(edges, used, 0, n - 1, sunLimit + rnd.next(1, 10), 1);
    } else if (mode == 2) {
        addEdge(edges, used, 0, n - 1, rnd.next(1, sunLimit), 1);
    } else if (mode == 3) {
        addEdge(edges, used, 0, n - 1, rnd.next(25, 60), 0);
    }

    vector<pair<int, int>> candidates;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (!used[i][j]) candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extra = candidates.empty() ? 0 : rnd.next(0, min<int>(candidates.size(), 18));
    for (int i = 0; i < extra; ++i) {
        int d = rnd.next(1, mode == 5 ? 10000 : 60);
        int u = rnd.next(0, 1);
        addEdge(edges, used, candidates[i].first, candidates[i].second, d, u);
    }

    if (edges.empty()) {
        addEdge(edges, used, 0, 1, rnd.next(1, 20), rnd.next(0, 1));
    }

    shuffle(edges.begin(), edges.end());

    println(sunLimit);
    println(n, static_cast<int>(edges.size()));
    for (const Edge& edge : edges) {
        println(edge.s, edge.t, edge.d, edge.u);
    }

    return 0;
}
