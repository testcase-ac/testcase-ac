#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> relabelAndShuffle(int n, vector<pair<int, int>> edges) {
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());

    for (auto& edge : edges) {
        edge.first = perm[edge.first];
        edge.second = perm[edge.second];
        if (rnd.next(2) == 0) swap(edge.first, edge.second);
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) edges.emplace_back(v - 1, v);
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) edges.emplace_back(center, v);
    }
    return edges;
}

vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) edges.emplace_back(v / 2, v);
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(1, n);
    for (int v = 2; v <= handle; ++v) edges.emplace_back(v - 1, v);
    for (int v = handle + 1; v <= n; ++v) edges.emplace_back(handle, v);
    return edges;
}

vector<pair<int, int>> makeDoubleStar(int n) {
    vector<pair<int, int>> edges;
    if (n == 1) return edges;

    edges.emplace_back(1, 2);
    for (int v = 3; v <= n; ++v) {
        edges.emplace_back(rnd.next(1, 2), v);
    }
    return edges;
}

vector<pair<int, int>> makeRandomParentTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int bias = rnd.next(-2, 3);
        int parent = rnd.wnext(v - 1, bias) + 1;
        edges.emplace_back(parent, v);
    }
    return edges;
}

vector<pair<int, int>> makeTree(int n) {
    if (n == 1) return {};

    int mode = rnd.next(6);
    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges = makePath(n);
    } else if (mode == 1) {
        edges = makeStar(n);
    } else if (mode == 2) {
        edges = makeBinaryTree(n);
    } else if (mode == 3) {
        edges = makeBroom(n);
    } else if (mode == 4) {
        edges = makeDoubleStar(n);
    } else {
        edges = makeRandomParentTree(n);
    }
    return relabelAndShuffle(n, edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 14);
    int t = rnd.next(1, 8);

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println(n);
        for (auto [u, v] : makeTree(n)) {
            println(u, v);
        }
    }

    return 0;
}
