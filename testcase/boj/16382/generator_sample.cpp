#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({i, i + 1});
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

vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.push_back({v / 2, v});
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(1, n);
    for (int i = 1; i < handle; ++i) {
        edges.push_back({i, i + 1});
    }
    int center = rnd.next(1, handle);
    for (int v = handle + 1; v <= n; ++v) {
        edges.push_back({center, v});
    }
    return edges;
}

vector<pair<int, int>> makeRandomRecursiveTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.push_back({rnd.next(1, v - 1), v});
    }
    return edges;
}

void relabelAndShuffle(vector<pair<int, int>>& edges, int n) {
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) {
        perm[i] = i;
    }
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

    int n = rnd.next(1, 14);
    int t = rnd.next(1, min(6, 200000 / n));

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = n == 1 ? 0 : rnd.next(0, 4);
        vector<pair<int, int>> edges;

        if (mode == 0) {
            edges = makePath(n);
        } else if (mode == 1) {
            edges = makeStar(n);
        } else if (mode == 2) {
            edges = makeBinaryTree(n);
        } else if (mode == 3) {
            edges = makeBroom(n);
        } else {
            edges = makeRandomRecursiveTree(n);
        }

        relabelAndShuffle(edges, n);

        println(n);
        for (const auto& edge : edges) {
            println(edge.first, edge.second);
        }
    }
}
