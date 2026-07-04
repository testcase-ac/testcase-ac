#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, i + 1);
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) {
            edges.emplace_back(center, v);
        }
    }
    return edges;
}

vector<pair<int, int>> makeBalancedTree(int n) {
    vector<pair<int, int>> edges;
    int maxChildren = rnd.next(2, 4);
    for (int v = 2; v <= n; ++v) {
        int parent = max(1, (v - 2) / maxChildren + 1);
        edges.emplace_back(parent, v);
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(1, n);
    for (int i = 1; i < handle; ++i) {
        edges.emplace_back(i, i + 1);
    }
    int hub = rnd.next(1, handle);
    for (int v = handle + 1; v <= n; ++v) {
        edges.emplace_back(hub, v);
    }
    return edges;
}

vector<pair<int, int>> makeCaterpillar(int n) {
    vector<pair<int, int>> edges;
    int spine = rnd.next(1, n);
    for (int i = 1; i < spine; ++i) {
        edges.emplace_back(i, i + 1);
    }
    for (int v = spine + 1; v <= n; ++v) {
        edges.emplace_back(rnd.next(1, spine), v);
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = rnd.next(1, v - 1);
        edges.emplace_back(parent, v);
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 35);
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(80, 180);
    } else {
        n = rnd.next(2, 60);
    }

    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges = makePath(n);
    } else if (mode == 1) {
        edges = makeStar(n);
    } else if (mode == 2) {
        edges = makeBalancedTree(n);
    } else if (mode == 3) {
        edges = makeBroom(n);
    } else if (mode == 4) {
        edges = makeCaterpillar(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin() + 1, perm.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [a, b] : edges) {
        a = perm[a];
        b = perm[b];
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}
