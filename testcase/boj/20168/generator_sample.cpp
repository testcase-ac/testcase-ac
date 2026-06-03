#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v,
                    int w) {
    pair<int, int> key = minmax(u, v);
    if (used.insert(key).second) {
        edges.push_back({u, v, w});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) ++b;

    int mode = rnd.next(0, 4);
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());
    vertices.erase(find(vertices.begin(), vertices.end(), a));
    vertices.erase(find(vertices.begin(), vertices.end(), b));

    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        int w = rnd.next(1, 1000);
        int c = rnd.next(1, min(10000, max(1, w - 1)));
        addEdge(edges, used, a, b, w);
        println(n, (int)edges.size(), a, b, c);
    } else {
        int pathLen = rnd.next(1, min(n - 1, 5));
        vector<int> path = {a};
        for (int i = 0; i + 1 < pathLen; ++i) path.push_back(vertices[i]);
        path.push_back(b);

        int pathSum = 0;
        int maxOnPath = 0;
        for (int i = 0; i + 1 < (int)path.size(); ++i) {
            int w = rnd.next(1, mode == 1 ? 20 : 1000);
            pathSum += w;
            maxOnPath = max(maxOnPath, w);
            addEdge(edges, used, path[i], path[i + 1], w);
        }

        if (mode == 2 || mode == 3) {
            int candidates = n * (n - 1) / 2;
            int target = mode == 2 ? rnd.next((int)edges.size(), min(candidates, 15))
                                   : rnd.next(max((int)edges.size(), candidates / 2), candidates);
            vector<pair<int, int>> pairs;
            for (int u = 1; u <= n; ++u) {
                for (int v = u + 1; v <= n; ++v) {
                    if (!used.count({u, v})) pairs.push_back({u, v});
                }
            }
            shuffle(pairs.begin(), pairs.end());
            for (auto [u, v] : pairs) {
                if ((int)edges.size() >= target) break;
                int w = rnd.next(1, mode == 2 ? 30 : 1000);
                addEdge(edges, used, u, v, w);
            }
        }

        int cMode = rnd.next(0, 3);
        int c;
        if (cMode == 0) {
            c = rnd.next(1, max(1, pathSum - 1));
        } else if (cMode == 1) {
            c = pathSum;
        } else {
            c = rnd.next(pathSum, 10000);
        }

        if (mode == 4 && n >= 3) {
            int detour = vertices.empty() ? (a == 1 ? 2 : 1) : vertices[0];
            int heavy = rnd.next(maxOnPath + 1, 1000);
            addEdge(edges, used, a, detour, heavy);
            addEdge(edges, used, detour, b, rnd.next(1, max(1, min(heavy, 1000))));
        }

        shuffle(edges.begin(), edges.end());
        println(n, (int)edges.size(), a, b, c);
    }

    for (const Edge& e : edges) {
        println(e.u, e.v, e.w);
    }

    return 0;
}
