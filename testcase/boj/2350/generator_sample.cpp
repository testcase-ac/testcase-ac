#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int widthByMode(int mode) {
    static const vector<int> interestingWidths = {1, 2, 3, 5, 10, 50, 100, 199, 200};

    if (mode == 0) {
        return rnd.next(1, 200);
    }
    if (mode == 1) {
        return interestingWidths[rnd.next(static_cast<int>(interestingWidths.size()))];
    }
    return rnd.wnext(200, rnd.next(-2, 2)) + 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = mode == 0 ? 1 : rnd.next(2, 12);
    int widthMode = rnd.next(0, 2);

    vector<Edge> edges;
    if (n > 1) {
        if (mode == 1) {
            for (int city = 2; city <= n; ++city) {
                edges.push_back({1, city, widthByMode(widthMode)});
            }
        } else if (mode == 2) {
            for (int city = 1; city < n; ++city) {
                edges.push_back({city, city + 1, widthByMode(widthMode)});
            }
        } else {
            vector<int> parent(n + 1);
            for (int city = 2; city <= n; ++city) {
                parent[city] = rnd.next(1, city - 1);
                edges.push_back({city, parent[city], widthByMode(widthMode)});
            }
        }
    }

    vector<pair<int, int>> simplePairs;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            simplePairs.push_back({u, v});
        }
    }
    shuffle(simplePairs.begin(), simplePairs.end());

    int extraSimple = 0;
    if (!simplePairs.empty()) {
        extraSimple = rnd.next(0, min<int>(simplePairs.size(), mode >= 3 ? n * 2 : n));
    }
    for (int i = 0; i < extraSimple; ++i) {
        edges.push_back({simplePairs[i].first, simplePairs[i].second, widthByMode(widthMode)});
    }

    if (mode >= 4) {
        int specialEdges = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < specialEdges; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            edges.push_back({u, v, widthByMode(widthMode)});
        }
    }

    shuffle(edges.begin(), edges.end());

    int k = rnd.next(0, min(18, max(0, n * 2)));
    if (mode == 0) {
        k = rnd.next(0, 3);
    }

    vector<pair<int, int>> routes;
    for (int i = 0; i < k; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (mode <= 3 && n > 1 && u == v) {
            v = u % n + 1;
        }
        routes.push_back({u, v});
    }

    println(n, static_cast<int>(edges.size()), k);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }
    for (const auto& route : routes) {
        println(route.first, route.second);
    }

    return 0;
}
