#include "testlib.h"

#include <algorithm>
#include <numeric>
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

vector<pair<int, int>> makeStar(int n, int center) {
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            edges.emplace_back(center, i);
        }
    }
    return edges;
}

vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(i / 2, i);
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, max(2, n - 2));
    for (int i = 1; i < handle; ++i) {
        edges.emplace_back(i, i + 1);
    }
    for (int i = handle + 1; i <= n; ++i) {
        edges.emplace_back(handle, i);
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(i, rnd.next(1, i - 1));
    }
    return edges;
}

void relabel(int n, int& p, vector<pair<int, int>>& edges) {
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    p = label[p];
    for (auto& [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(2) == 0) {
            swap(u, v);
        }
    }
    shuffle(edges.begin(), edges.end());
}

int clampHeight(int x) {
    return max(1, min(1000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = mode == 0 ? 1 : rnd.next(2, 14);
    int p = rnd.next(1, n);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        edges = {};
    } else if (mode == 1) {
        edges = makePath(n);
        p = rnd.any(vector<int>{1, n, rnd.next(1, n)});
    } else if (mode == 2) {
        p = rnd.next(1, n);
        edges = makeStar(n, p);
    } else if (mode == 3) {
        edges = makeBroom(n);
        p = rnd.next(1, n);
    } else if (mode == 4) {
        edges = makeBinaryTree(n);
        p = rnd.next(1, n);
    } else {
        edges = makeRandomTree(n);
        p = rnd.next(1, n);
    }

    vector<int> a(n + 1), b(n + 1);
    int heightMode = rnd.next(5);
    for (int i = 1; i <= n; ++i) {
        if (heightMode == 0) {
            a[i] = rnd.next(1, 12);
            b[i] = a[i];
        } else if (heightMode == 1) {
            a[i] = rnd.next(1, 20);
            b[i] = clampHeight(a[i] + rnd.next(-8, 12));
        } else if (heightMode == 2) {
            a[i] = (i % 2 == 0 ? 1000 : 1);
            b[i] = (i % 2 == 0 ? 1 : 1000);
        } else if (heightMode == 3) {
            a[i] = rnd.next(900, 1000);
            b[i] = rnd.next(1, 120);
        } else {
            a[i] = rnd.next(1, 120);
            b[i] = rnd.next(880, 1000);
        }
    }

    relabel(n, p, edges);

    vector<int> outA, outB;
    for (int i = 1; i <= n; ++i) {
        outA.push_back(a[i]);
        outB.push_back(b[i]);
    }

    println(n, p);
    println(outA);
    println(outB);
    for (auto [u, v] : edges) {
        println(u, v);
    }

    return 0;
}
