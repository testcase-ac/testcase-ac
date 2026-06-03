#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

static vector<pair<int, int>> makeTree(int n) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        int parent = rnd.next(0, i - 1);
        edges.push_back({order[i], order[parent]});
    }
    return edges;
}

static vector<pair<int, int>> makeForest(int n) {
    vector<pair<int, int>> edges;
    int components = rnd.next(2, min(n, 4));
    for (int i = components + 1; i <= n; ++i) {
        int parent = rnd.next(1, i - 1);
        edges.push_back({i, parent});
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

static vector<pair<int, int>> makeCycleGraph(int n) {
    vector<pair<int, int>> edges = makeTree(n);
    int a = rnd.next(1, n);
    int b = rnd.next(1, n);
    while (b == a) b = rnd.next(1, n);
    edges.push_back({a, b});
    shuffle(edges.begin(), edges.end());
    return edges;
}

static vector<pair<int, int>> makeNoisyGraph(int n) {
    vector<pair<int, int>> edges;
    int m = rnd.next(1, min(2 * n + 3, 30));
    for (int i = 0; i < m; ++i) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (rnd.next(4) == 0) b = a;
        edges.push_back({a, b});
        if (rnd.next(5) == 0) edges.push_back({a, b});
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = (mode == 0 ? 1 : rnd.next(2, 15));
        vector<pair<int, int>> edges;

        if (mode == 0) {
            edges = {};
        } else if (mode == 1) {
            edges = makeTree(n);
        } else if (mode == 2) {
            edges = makeForest(n);
        } else if (mode == 3) {
            edges = makeCycleGraph(n);
        } else if (mode == 4) {
            edges = makeNoisyGraph(n);
        } else {
            edges = makeTree(n);
            if (!edges.empty()) edges.push_back(rnd.any(edges));
        }

        println(n);
        println(static_cast<int>(edges.size()));
        for (auto [a, b] : edges) println(a, b);
    }

    return 0;
}
