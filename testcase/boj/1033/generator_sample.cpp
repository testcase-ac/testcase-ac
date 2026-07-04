#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

vector<Edge> makeChain(int n) {
    vector<Edge> edges;
    for (int i = 0; i + 1 < n; ++i) {
        edges.emplace_back(i, i + 1);
    }
    return edges;
}

vector<Edge> makeStar(int n) {
    vector<Edge> edges;
    int center = rnd.next(0, n - 1);
    for (int i = 0; i < n; ++i) {
        if (i != center) edges.emplace_back(center, i);
    }
    return edges;
}

vector<Edge> makeBinaryTree(int n) {
    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back((i - 1) / 2, i);
    }
    return edges;
}

vector<Edge> makeRandomTree(int n) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        int parent = rnd.next(0, i - 1);
        edges.emplace_back(order[parent], order[i]);
    }
    return edges;
}

pair<int, int> chooseRatio(int mode) {
    if (mode == 0) {
        return {rnd.next(1, 9), rnd.next(1, 9)};
    }
    if (mode == 1) {
        vector<pair<int, int>> ratios = {
            {1, 1}, {2, 3}, {3, 2}, {4, 6}, {6, 4}, {8, 9}, {9, 8}
        };
        return rnd.any(ratios);
    }
    return {rnd.next(6, 9), rnd.next(6, 9)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    int shape = rnd.next(4);
    int ratioMode = rnd.next(3);

    vector<Edge> edges;
    if (shape == 0) {
        edges = makeChain(n);
    } else if (shape == 1) {
        edges = makeStar(n);
    } else if (shape == 2) {
        edges = makeBinaryTree(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> relabel(n);
    iota(relabel.begin(), relabel.end(), 0);
    shuffle(relabel.begin(), relabel.end());

    println(n);
    shuffle(edges.begin(), edges.end());
    for (auto [a, b] : edges) {
        a = relabel[a];
        b = relabel[b];
        if (rnd.next(2)) swap(a, b);

        auto [p, q] = chooseRatio(ratioMode);
        println(a, b, p, q);
    }

    return 0;
}
