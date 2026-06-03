#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
    int p;
};

long long randomWeight(int mode) {
    if (mode == 0) {
        return rnd.next(0, 20);
    }
    if (mode == 1) {
        return rnd.any(vector<long long>{0, 1, 2, 1000000000LL});
    }
    return rnd.next(0LL, 1000LL);
}

long long randomX() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return 0;
    }
    if (mode == 1) {
        return rnd.next(1LL, 20LL);
    }
    if (mode == 2) {
        return rnd.next(21LL, 1000LL);
    }
    return rnd.next(900000000LL, 1000000000LL);
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int u, int v, long long w, int p) {
    if (u == v) {
        return;
    }
    pair<int, int> key = minmax(u, v);
    if (!used.insert(key).second) {
        return;
    }
    edges.push_back({u, v, w, p});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int colorMode = rnd.next(0, 3);
        for (int i = 1; i < n; ++i) {
            int color = colorMode == 0 ? i % 3 : rnd.next(0, 2);
            addEdge(edges, used, i, i + 1, randomWeight(rnd.next(0, 2)), color);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        for (int i = 2; i <= n; ++i) {
            addEdge(edges, used, i, rnd.next(1, i - 1), randomWeight(rnd.next(0, 2)), rnd.next(0, 2));
        }

        int extra = rnd.next(0, min(20, n * (n - 1) / 2 - (n - 1)));
        for (int tries = 0; tries < 200 && extra > 0; ++tries) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n);
            size_t before = edges.size();
            addEdge(edges, used, u, v, randomWeight(rnd.next(0, 2)), rnd.next(0, 2));
            if (edges.size() != before) {
                --extra;
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        vector<int> middle;
        for (int i = 2; i < n; ++i) {
            middle.push_back(i);
        }
        shuffle(middle.begin(), middle.end());

        int split = rnd.next(0, (int)middle.size());
        int prev = 1;
        for (int i = 0; i < split; ++i) {
            addEdge(edges, used, prev, middle[i], randomWeight(0), 1);
            prev = middle[i];
        }
        addEdge(edges, used, prev, n, randomWeight(0), 1);

        prev = 1;
        for (int i = split; i < (int)middle.size(); ++i) {
            addEdge(edges, used, prev, middle[i], randomWeight(0), 2);
            prev = middle[i];
        }
        addEdge(edges, used, prev, n, randomWeight(0), 2);

        if (n > 3) {
            addEdge(edges, used, rnd.next(2, n - 1), rnd.next(2, n - 1), randomWeight(0), 0);
        }
    } else {
        n = rnd.next(2, 10);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (j == i + 1 || rnd.next(0, 99) < 45) {
                    addEdge(edges, used, i, j, randomWeight(rnd.next(0, 2)), rnd.next(0, 2));
                }
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), randomX());
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w, edge.p);
    }

    return 0;
}
