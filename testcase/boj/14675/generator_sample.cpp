#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

static vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) edges.push_back({i, i + 1});
    return edges;
}

static vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) edges.push_back({center, v});
    }
    return edges;
}

static vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int spine = rnd.next(2, max(2, n - 1));
    for (int i = 1; i < spine; ++i) edges.push_back({i, i + 1});
    for (int v = spine + 1; v <= n; ++v) edges.push_back({spine, v});
    return edges;
}

static vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) edges.push_back({v / 2, v});
    return edges;
}

static vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int bias = rnd.next(0, 2);
        int parent;
        if (bias == 0) parent = rnd.next(1, v - 1);
        else if (bias == 1) parent = max(1, v - rnd.next(1, min(4, v - 1)));
        else parent = rnd.next(1, max(1, v / 2));
        edges.push_back({parent, v});
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) n = rnd.next(2, 14);
    else n = rnd.next(3, 14);

    vector<pair<int, int>> edges;
    if (mode == 0) edges = makePath(n);
    else if (mode == 1) edges = makeStar(n);
    else if (mode == 2) edges = makeBroom(n);
    else if (mode == 3) edges = makeBinaryTree(n);
    else edges = makeRandomTree(n);

    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end());
    for (auto& edge : edges) {
        edge.first = perm[edge.first];
        edge.second = perm[edge.second];
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }
    shuffle(edges.begin(), edges.end());

    vector<int> degree(n + 1, 0);
    for (auto edge : edges) {
        ++degree[edge.first];
        ++degree[edge.second];
    }

    vector<int> leaves, internal;
    for (int v = 1; v <= n; ++v) {
        if (degree[v] == 1) leaves.push_back(v);
        else internal.push_back(v);
    }

    int q = rnd.next(1, min(30, 3 * n));
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int kind = rnd.next(0, 4);
        if (kind <= 2) {
            int vertex;
            if (kind == 0 && !leaves.empty()) vertex = rnd.any(leaves);
            else if (kind == 1 && !internal.empty()) vertex = rnd.any(internal);
            else vertex = rnd.next(1, n);
            queries.push_back({1, vertex});
        } else {
            int edgeIndex;
            if (kind == 3) edgeIndex = rnd.next(1, n - 1);
            else edgeIndex = rnd.any(vector<int>{1, n - 1});
            queries.push_back({2, edgeIndex});
        }
    }

    println(n);
    for (auto edge : edges) println(edge.first, edge.second);
    println(q);
    for (auto query : queries) println(query.first, query.second);

    return 0;
}
