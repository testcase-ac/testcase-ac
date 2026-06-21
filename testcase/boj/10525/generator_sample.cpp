#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int node = 2; node <= n; ++node) {
        edges.push_back({node - 1, node});
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int node = 1; node <= n; ++node) {
        if (node != center) {
            edges.push_back({center, node});
        }
    }
    return edges;
}

vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int node = 2; node <= n; ++node) {
        edges.push_back({node / 2, node});
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, n);
    for (int node = 2; node <= handle; ++node) {
        edges.push_back({node - 1, node});
    }
    for (int node = handle + 1; node <= n; ++node) {
        edges.push_back({handle, node});
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int node = 2; node <= n; ++node) {
        int parent = rnd.next(1, node - 1);
        edges.push_back({parent, node});
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 1) {
        n = rnd.next(2, 45);
    } else if (mode == 2) {
        n = rnd.next(3, 31);
    } else {
        n = rnd.next(2, 60);
    }

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
        edges = makeRandomTree(n);
    }

    vector<int> label(n + 1);
    for (int node = 1; node <= n; ++node) {
        label[node] = node;
    }
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
