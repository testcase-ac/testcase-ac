#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> relabelEdges(int n, vector<pair<int, int>> edges) {
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

vector<pair<int, int>> pathTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({i, i + 1});
    }
    return edges;
}

vector<pair<int, int>> starTree(int n) {
    vector<pair<int, int>> edges;
    int center = 1;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({center, i});
    }
    return edges;
}

vector<pair<int, int>> binaryHeapTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i / 2, i});
    }
    return edges;
}

vector<pair<int, int>> broomTree(int n) {
    vector<pair<int, int>> edges;
    int pathLength = rnd.next(2, max(2, n - 1));
    for (int i = 1; i < pathLength; ++i) {
        edges.push_back({i, i + 1});
    }
    int hub = rnd.next(1, pathLength);
    for (int i = pathLength + 1; i <= n; ++i) {
        edges.push_back({hub, i});
    }
    return edges;
}

vector<pair<int, int>> randomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i, rnd.next(1, i - 1)});
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n;
        vector<pair<int, int>> edges;

        if (mode == 0) {
            n = rnd.next(2, 14);
            edges = pathTree(n);
        } else if (mode == 1) {
            n = rnd.next(3, 16);
            edges = starTree(n);
        } else if (mode == 2) {
            n = rnd.any(vector<int>{3, 5, 7, 9, 11, 13, 15});
            edges = binaryHeapTree(n);
        } else if (mode == 3) {
            n = rnd.next(4, 18);
            edges = broomTree(n);
        } else {
            n = rnd.next(2, 20);
            edges = randomTree(n);
        }

        edges = relabelEdges(n, edges);
        println(n);
        for (const auto& edge : edges) {
            println(edge.first, edge.second);
        }
    }

    return 0;
}
