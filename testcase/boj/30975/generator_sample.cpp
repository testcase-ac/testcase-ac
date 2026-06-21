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

static void addEdge(vector<Edge>& edges, int u, int v, int w) {
    edges.push_back({u, v, w});
}

static void addRandomEdge(vector<Edge>& edges, int n) {
    int u = rnd.next(1, n + 1);
    int v = rnd.next(1, n + 1);
    while (u == v) {
        v = rnd.next(1, n + 1);
    }
    addEdge(edges, u, v, rnd.next(1, 100));
}

static vector<int> makePrecedence(int n, const vector<int>& order, int mode) {
    vector<int> p(n + 1);
    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
        }
    } else if (mode == 1) {
        p[order[0]] = order[0];
        for (int i = 1; i < n; ++i) {
            p[order[i]] = order[i - 1];
        }
    } else if (mode == 2 && n >= 2) {
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
        }
        p[order[0]] = order[1];
        p[order[1]] = order[0];
    } else {
        for (int i = 1; i <= n; ++i) {
            p[i] = rnd.next(1, n);
        }
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 4) {
        n = 14;
    } else if (mode == 0) {
        n = rnd.next(1, 3);
    } else {
        n = rnd.next(2, 9);
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    int precedenceMode = mode == 2 ? 2 : rnd.next(0, 3);
    vector<int> p = makePrecedence(n, order, precedenceMode);

    vector<Edge> edges;
    if (mode != 0) {
        addEdge(edges, n + 1, order[0], rnd.next(1, 20));
        for (int i = 1; i < n; ++i) {
            addEdge(edges, order[i - 1], order[i], rnd.next(1, 20));
        }
        addEdge(edges, order.back(), n + 1, rnd.next(1, 20));
    } else {
        addRandomEdge(edges, n);
    }

    if (mode == 1 || mode == 3) {
        int duplicateCount = rnd.next(1, min(12, 200 - int(edges.size())));
        for (int i = 0; i < duplicateCount; ++i) {
            Edge base = rnd.any(edges);
            addEdge(edges, base.u, base.v, rnd.next(1, 100));
        }
    }

    int targetM;
    if (mode == 4) {
        targetM = rnd.next(35, 80);
    } else if (mode == 3) {
        targetM = rnd.next(max(1, int(edges.size())), min(200, int(edges.size()) + 45));
    } else {
        targetM = rnd.next(max(1, int(edges.size())), min(200, int(edges.size()) + 18));
    }

    while (int(edges.size()) < targetM) {
        addRandomEdge(edges, n);
    }
    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << p[i];
    }
    cout << '\n';
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }

    return 0;
}
