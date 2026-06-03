#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 4) {
        n = rnd.next(8, 13);
    } else {
        n = rnd.next(3, 10);
    }

    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    if (n >= 2) {
        vector<int> vertices(n);
        iota(vertices.begin(), vertices.end(), 1);
        shuffle(vertices.begin(), vertices.end());

        for (int i = 1; i < n; ++i) {
            int parent = vertices[rnd.next(0, i - 1)];
            int child = vertices[i];
            pair<int, int> edge = minmax(parent, child);
            edges.push_back(edge);
            used.insert(edge);
        }
    }

    int maxEdges = static_cast<int>(candidates.size());
    int targetM = static_cast<int>(edges.size());
    if (mode == 0) {
        targetM = n - 1;
    } else if (mode == 1) {
        targetM = min(maxEdges, n);
    } else if (mode == 2) {
        targetM = rnd.next(n, min(maxEdges, n + 3));
    } else if (mode == 3) {
        targetM = rnd.next(n - 1, min(maxEdges, 2 * n));
    } else if (mode == 4) {
        targetM = rnd.next(min(maxEdges, 2 * n), min(maxEdges, 4 * n));
    } else {
        targetM = rnd.next(n - 1, maxEdges);
    }

    for (auto edge : candidates) {
        if (static_cast<int>(edges.size()) >= targetM) {
            break;
        }
        if (used.insert(edge).second) {
            edges.push_back(edge);
        }
    }

    shuffle(edges.begin(), edges.end());

    vector<long long> weights;
    int m = static_cast<int>(edges.size());
    long long base = rnd.next(-1000000, 1000000);
    long long step = rnd.next(1, 1000);
    for (int i = 0; i < m; ++i) {
        weights.push_back(base + step * i);
    }
    shuffle(weights.begin(), weights.end());

    println(n, m);
    for (int i = 0; i < m; ++i) {
        println(edges[i].first, edges[i].second, weights[i]);
    }

    return 0;
}
