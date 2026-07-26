#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode == 1) {
        n = rnd.next(3, 7);
    } else if (sizeMode == 2) {
        n = rnd.next(8, 18);
    } else if (sizeMode == 3) {
        n = rnd.next(19, 45);
    } else {
        n = rnd.next(46, 120);
    }

    int qMode = rnd.next(0, 4);
    int q;
    if (qMode == 0) {
        q = 1;
    } else if (qMode == 1) {
        q = rnd.next(2, 8);
    } else if (qMode == 2) {
        q = rnd.next(9, 25);
    } else if (qMode == 3) {
        q = rnd.next(26, 70);
    } else {
        q = rnd.next(71, 140);
    }

    auto randomWeight = [&]() -> int {
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            return 1;
        }
        if (mode == 1) {
            return rnd.next(2, 10);
        }
        if (mode == 2) {
            return rnd.next(11, 100);
        }
        if (mode == 3) {
            return rnd.next(1000, 100000);
        }
        if (mode == 4) {
            return 1000000000;
        }
        return rnd.next(1, 1000000000);
    };

    vector<tuple<int, int, int>> edges;
    int treeMode = rnd.next(0, 5);
    if (treeMode == 0) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({i, i + 1, randomWeight()});
        }
    } else if (treeMode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.push_back({center, i, randomWeight()});
            }
        }
    } else if (treeMode == 2) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            edges.push_back({i, i + 1, randomWeight()});
        }
        for (int i = spine + 1; i <= n; ++i) {
            edges.push_back({rnd.next(1, spine), i, randomWeight()});
        }
    } else if (treeMode == 3) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i, randomWeight()});
        }
    } else if (treeMode == 4) {
        for (int i = 2; i <= n; ++i) {
            int parent = max(1, i - rnd.next(1, min(i - 1, 5)));
            edges.push_back({parent, i, randomWeight()});
        }
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parentIndex = rnd.next(0, i - 1);
            edges.push_back({order[parentIndex], order[i], randomWeight()});
        }
    }

    shuffle(edges.begin(), edges.end());

    vector<vector<pair<int, int>>> adj(n + 1);
    for (auto [u, v, w] : edges) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto distancesFrom = [&](int source) {
        vector<long long> dist(n + 1, -1);
        vector<int> stack = {source};
        dist[source] = 0;
        while (!stack.empty()) {
            int x = stack.back();
            stack.pop_back();
            for (auto [to, w] : adj[x]) {
                if (dist[to] == -1) {
                    dist[to] = dist[x] + w;
                    stack.push_back(to);
                }
            }
        }
        return dist;
    };

    vector<long long> distFrom1 = distancesFrom(1);
    vector<long long> distFromN = distancesFrom(n);
    long long diameterProbe = 0;
    for (int i = 1; i <= n; ++i) {
        diameterProbe = max(diameterProbe, max(distFrom1[i], distFromN[i]));
    }

    vector<string> scenarios;
    vector<int> activeAdds;

    auto pickVertex = [&]() -> int {
        int mode = rnd.next(0, 5);
        if (mode == 0) {
            return 1;
        }
        if (mode == 1) {
            return n;
        }
        if (mode == 2 && n >= 3) {
            return rnd.next(2, n - 1);
        }
        return rnd.next(1, n);
    };

    auto pickRange = [&](int vertex) -> long long {
        int mode = rnd.next(0, 8);
        if (mode == 0) {
            return 1;
        }
        if (mode == 1) {
            return rnd.next(1, 10);
        }
        if (mode == 2) {
            return rnd.next(1, 1000);
        }
        if (mode == 3) {
            return max(1LL, min(1000000000000000LL, distFrom1[vertex] + rnd.next(0, 5)));
        }
        if (mode == 4) {
            return max(1LL, min(1000000000000000LL, distFromN[vertex] + rnd.next(0, 5)));
        }
        if (mode == 5) {
            return min(1000000000000000LL, diameterProbe + rnd.next(0, 20));
        }
        if (mode == 6) {
            return 1000000000000000LL;
        }
        if (mode == 7) {
            return rnd.next(1LL, 1000000000000LL);
        }
        return rnd.next(1LL, 1000000000000000LL);
    };

    int addBias = rnd.next(45, 85);
    for (int j = 1; j <= q; ++j) {
        bool canDelete = !activeAdds.empty();
        bool doAdd = !canDelete || rnd.next(0, 99) < addBias;
        if (doAdd) {
            int vertex = pickVertex();
            long long range = pickRange(vertex);
            scenarios.push_back(format("1 %d %lld", vertex, range));
            activeAdds.push_back(j);
        } else {
            int pos = rnd.next(0, (int)activeAdds.size() - 1);
            int removed = activeAdds[pos];
            scenarios.push_back(format("2 %d", removed));
            activeAdds[pos] = activeAdds.back();
            activeAdds.pop_back();
        }
    }

    println(n, q);
    for (auto [u, v, w] : edges) {
        println(u, v, w);
    }
    for (const string& scenario : scenarios) {
        println(scenario);
    }
    return 0;
}
