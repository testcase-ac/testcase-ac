#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

using Edge = tuple<int, int, int>;

int edgeLength() {
    int mode = rnd.next(5);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return 10000;
    }
    if (mode == 2) {
        return rnd.next(1, 10);
    }
    return rnd.next(1, 10000);
}

void addEdge(vector<Edge>& edges, int u, int v) {
    edges.emplace_back(u, v, edgeLength());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(6);
    int n;
    if (shape == 0) {
        n = 1;
    } else if (rnd.next(5) == 0) {
        n = rnd.next(12, 20);
    } else {
        n = rnd.next(2, 12);
    }

    int mMode = rnd.next(6);
    int m;
    if (mMode == 0) {
        m = 1;
    } else if (mMode == 1) {
        m = n;
    } else if (mMode == 2) {
        m = rnd.next(1, min(30, 2500));
    } else if (mMode == 3) {
        m = rnd.next(100, 2500);
    } else {
        m = rnd.next(1, 2500);
    }

    vector<Edge> edges;
    if (shape == 1) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, v - 1, v);
        }
    } else if (shape == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                addEdge(edges, center, v);
            }
        }
    } else if (shape == 3) {
        int spine = max(2, n / 2);
        for (int v = 2; v <= spine; ++v) {
            addEdge(edges, v - 1, v);
        }
        for (int v = spine + 1; v <= n; ++v) {
            addEdge(edges, rnd.next(1, spine), v);
        }
    } else if (shape == 4) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, max(1, v / 2), v);
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int parent;
            if (rnd.next(4) == 0) {
                parent = 1;
            } else {
                parent = rnd.next(1, v - 1);
            }
            addEdge(edges, parent, v);
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n, m);
    for (const Edge& edge : edges) {
        int u, v, length;
        tie(u, v, length) = edge;
        if (rnd.next(2) == 0) {
            swap(u, v);
        }
        println(label[u], label[v], length);
    }

    return 0;
}
