#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    long long c;
};

long long randomCost(int index) {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return rnd.next(1, 20);
    }
    if (mode == 1) {
        return rnd.next(1, 1000);
    }
    if (mode == 2) {
        return 1000000000LL;
    }
    if (mode == 3) {
        return 1LL << rnd.next(0, 29);
    }
    return 1 + 1LL * index * rnd.next(1, 17);
}

void addEdge(vector<Edge>& edges, int u, int v, long long cost) {
    if (u > v) {
        swap(u, v);
    }
    edges.push_back({u, v, cost});
}

vector<Edge> makePath(int n) {
    vector<Edge> edges;
    for (int v = 1; v < n; ++v) {
        addEdge(edges, v, v + 1, randomCost(v));
    }
    return edges;
}

vector<Edge> makeStar(int n) {
    vector<Edge> edges;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) {
            addEdge(edges, center, v, randomCost(v));
        }
    }
    return edges;
}

vector<Edge> makeBroom(int n) {
    vector<Edge> edges;
    int handle = rnd.next(2, n);
    for (int v = 1; v < handle; ++v) {
        addEdge(edges, v, v + 1, randomCost(v));
    }
    for (int v = handle + 1; v <= n; ++v) {
        addEdge(edges, handle, v, randomCost(v));
    }
    return edges;
}

vector<Edge> makeBinaryTree(int n) {
    vector<Edge> edges;
    for (int v = 2; v <= n; ++v) {
        addEdge(edges, v / 2, v, randomCost(v));
    }
    return edges;
}

vector<Edge> makeRandomTree(int n) {
    vector<Edge> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = rnd.next(1, v - 1);
        addEdge(edges, parent, v, randomCost(v));
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 7);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(2, 14);
        int mode = rnd.next(0, 4);

        vector<Edge> edges;
        if (mode == 0) {
            edges = makePath(n);
        } else if (mode == 1) {
            edges = makeStar(n);
        } else if (mode == 2) {
            edges = makeBroom(n);
        } else if (mode == 3) {
            edges = makeBinaryTree(n);
        } else {
            edges = makeRandomTree(n);
        }

        shuffle(edges.begin(), edges.end());

        println(n);
        for (const Edge& edge : edges) {
            println(edge.a, edge.b, edge.c);
        }
    }

    return 0;
}
