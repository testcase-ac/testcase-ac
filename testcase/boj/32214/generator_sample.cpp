#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.push_back({v - 1, v});
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) {
            edges.push_back({center, v});
        }
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, n);
    for (int v = 2; v <= handle; ++v) {
        edges.push_back({v - 1, v});
    }
    for (int v = handle + 1; v <= n; ++v) {
        edges.push_back({handle, v});
    }
    return edges;
}

vector<pair<int, int>> makeCaterpillar(int n) {
    vector<pair<int, int>> edges;
    int spine = rnd.next(2, n);
    for (int v = 2; v <= spine; ++v) {
        edges.push_back({v - 1, v});
    }
    for (int v = spine + 1; v <= n; ++v) {
        edges.push_back({rnd.next(1, spine), v});
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = rnd.next(1, v - 1);
        edges.push_back({parent, v});
    }
    return edges;
}

void relabelAndPrint(int n, vector<pair<int, int>> edges) {
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(2) == 1) {
            swap(u, v);
        }
        println(u, v);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 18);
    } else {
        n = rnd.next(6, 25);
    }

    vector<pair<int, int>> edges;
    if (n == 1) {
        edges = {};
    } else if (mode == 0) {
        edges = makeRandomTree(n);
    } else if (mode == 1) {
        edges = makePath(n);
    } else if (mode == 2) {
        edges = makeStar(n);
    } else if (mode == 3) {
        edges = makeBroom(n);
    } else {
        edges = makeCaterpillar(n);
    }

    relabelAndPrint(n, edges);
    return 0;
}
