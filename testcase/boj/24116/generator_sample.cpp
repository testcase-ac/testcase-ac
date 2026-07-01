#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

void addEdge(vector<Edge>& edges, int a, int b, int c) {
    if (a > b) {
        swap(a, b);
    }
    edges.push_back({a, b, c});
}

int feeForMode(int mode, int index) {
    if (mode == 0) {
        return rnd.next(1, 12);
    }
    if (mode == 1) {
        return 100 - rnd.next(0, 8);
    }
    if (mode == 2) {
        return 1 + (index % 4);
    }
    return rnd.next(1, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    if (mode == 5) {
        n = rnd.next(2, 7);
    }

    int k;
    if (rnd.next(0, 4) == 0) {
        k = rnd.any(vector<int>{1, n});
    } else {
        k = rnd.next(1, n);
    }

    vector<Edge> edges;

    if (mode == 0) {
        for (int city = 1; city < n; ++city) {
            addEdge(edges, city, city + 1, feeForMode(mode, city));
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int city = 1; city <= n; ++city) {
            if (city != center) {
                addEdge(edges, center, city, feeForMode(mode, city));
            }
        }
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(edges, order[i], parent, feeForMode(mode, i));
        }
    }

    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            pairs.push_back({a, b});
        }
    }
    shuffle(pairs.begin(), pairs.end());

    int simpleTarget = rnd.next(n - 1, min<int>(pairs.size(), n + rnd.next(0, n)));
    if (mode == 3) {
        simpleTarget = rnd.next(n - 1, min<int>(pairs.size(), n * (n - 1) / 2));
    }

    for (const auto& [a, b] : pairs) {
        if ((int)edges.size() >= simpleTarget) {
            break;
        }
        bool alreadyPresent = false;
        for (const Edge& edge : edges) {
            if (edge.a == a && edge.b == b) {
                alreadyPresent = true;
                break;
            }
        }
        if (!alreadyPresent) {
            addEdge(edges, a, b, feeForMode(mode, edges.size()));
        }
    }

    if (mode == 4 || mode == 5) {
        int extra = rnd.next(1, min(8, n + 2));
        for (int i = 0; i < extra; ++i) {
            Edge base = rnd.any(edges);
            addEdge(edges, base.a, base.b, feeForMode(mode, i));
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), k);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.c);
    }

    return 0;
}
