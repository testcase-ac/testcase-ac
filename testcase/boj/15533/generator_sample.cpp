#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.push_back({1, v});
    }
    return edges;
}

static vector<pair<int, int>> makeChain(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.push_back({v - 1, v});
    }
    return edges;
}

static vector<pair<int, int>> makeBalanced(int n, int arity) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = (v + arity - 2) / arity;
        edges.push_back({parent, v});
    }
    return edges;
}

static vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, max(2, n - 1));

    for (int v = 2; v <= handle; ++v) {
        edges.push_back({v - 1, v});
    }
    for (int v = handle + 1; v <= n; ++v) {
        edges.push_back({handle, v});
    }
    return edges;
}

static vector<pair<int, int>> makeRandomRecursive(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int bias = rnd.next(-2, 2);
        int parent = rnd.wnext(v - 1, bias) + 1;
        edges.push_back({parent, v});
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 14);
    vector<pair<int, int>> edges;

    if (n == 1) {
        edges = {};
    } else {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            edges = makeStar(n);
        } else if (mode == 1) {
            edges = makeChain(n);
        } else if (mode == 2) {
            edges = makeBalanced(n, rnd.next(2, 3));
        } else if (mode == 3) {
            edges = makeBroom(n);
        } else {
            edges = makeRandomRecursive(n);
        }
    }

    if (rnd.next(0, 1) == 1) {
        shuffle(edges.begin(), edges.end());
    }

    println(n);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
