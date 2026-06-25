#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i - 1, i});
    }
    return edges;
}

static vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            edges.push_back({center, i});
        }
    }
    return edges;
}

static vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i / 2, i});
    }
    return edges;
}

static vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, max(2, n - 1));
    for (int i = 2; i <= handle; ++i) {
        edges.push_back({i - 1, i});
    }
    for (int i = handle + 1; i <= n; ++i) {
        edges.push_back({handle, i});
    }
    return edges;
}

static vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({rnd.next(1, i - 1), i});
    }
    return edges;
}

static void relabelTree(int n, vector<pair<int, int>>& edges) {
    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end());

    for (auto& edge : edges) {
        edge.first = perm[edge.first];
        edge.second = perm[edge.second];
        if (rnd.next(0, 1) == 1) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0) ? 1 : rnd.next(2, 14);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges = {};
    } else if (mode == 1) {
        edges = makePath(n);
    } else if (mode == 2) {
        edges = makeStar(n);
    } else if (mode == 3) {
        edges = makeBinaryTree(n);
    } else if (mode == 4) {
        edges = makeBroom(n);
    } else {
        edges = makeRandomTree(n);
    }
    relabelTree(n, edges);

    int blackCount = rnd.next(1, n);
    int m = rnd.next(1, blackCount);

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<int> black(n + 1, 0);
    for (int i = 0; i < blackCount; ++i) {
        black[order[i]] = 1;
    }

    vector<int> colors;
    for (int i = 1; i <= n; ++i) {
        colors.push_back(black[i]);
    }

    println(n, m);
    println(colors);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
