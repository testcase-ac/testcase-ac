#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> pathTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(i - 1, i);
    }
    return edges;
}

vector<pair<int, int>> starTree(int n) {
    int center = rnd.next(1, n);
    vector<pair<int, int>> edges;
    for (int v = 1; v <= n; ++v) {
        if (v != center) {
            edges.emplace_back(center, v);
        }
    }
    return edges;
}

vector<pair<int, int>> broomTree(int n) {
    int handle = rnd.next(2, n);
    vector<pair<int, int>> edges = pathTree(handle);
    int hub = rnd.next(1, handle);
    for (int v = handle + 1; v <= n; ++v) {
        edges.emplace_back(hub, v);
    }
    return edges;
}

vector<pair<int, int>> binaryLikeTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.emplace_back(v / 2, v);
    }
    return edges;
}

vector<pair<int, int>> randomRecursiveTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.emplace_back(rnd.next(1, v - 1), v);
    }
    return edges;
}

void relabelAndShuffle(int n, vector<pair<int, int>>& edges) {
    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges = pathTree(n);
    } else if (mode == 1) {
        edges = starTree(n);
    } else if (mode == 2) {
        edges = broomTree(n);
    } else if (mode == 3) {
        edges = binaryLikeTree(n);
    } else {
        edges = randomRecursiveTree(n);
    }

    relabelAndShuffle(n, edges);

    println(n);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
