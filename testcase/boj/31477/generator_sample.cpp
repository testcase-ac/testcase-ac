#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

static int randomWeight(int profile) {
    if (profile == 0) {
        return rnd.next(1, 6);
    }
    if (profile == 1) {
        return rnd.next(900, 1000);
    }
    if (profile == 2) {
        return rnd.next(1, 1000);
    }
    if (profile == 3) {
        return rnd.any(vector<int>{1, 2, 3, 998, 999, 1000});
    }
    return rnd.next(20, 80);
}

static void addEdge(vector<Edge>& edges, int a, int b, int profile) {
    edges.push_back({a, b, randomWeight(profile)});
}

static vector<Edge> makePath(int n, int profile) {
    vector<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        addEdge(edges, i - 1, i, profile);
    }
    return edges;
}

static vector<Edge> makeStar(int n, int profile) {
    vector<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        addEdge(edges, 1, i, profile);
    }
    return edges;
}

static vector<Edge> makeBinaryTree(int n, int profile) {
    vector<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        addEdge(edges, i / 2, i, profile);
    }
    return edges;
}

static vector<Edge> makeBroom(int n, int profile) {
    vector<Edge> edges;
    int handle = rnd.next(2, max(2, n - 1));
    for (int i = 2; i <= handle; ++i) {
        addEdge(edges, i - 1, i, profile);
    }
    for (int i = handle + 1; i <= n; ++i) {
        int attach = rnd.next(max(1, handle - 2), handle);
        addEdge(edges, attach, i, profile);
    }
    return edges;
}

static vector<Edge> makeRandomParentTree(int n, int profile) {
    vector<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        int parent;
        if (rnd.next(0, 3) == 0) {
            parent = 1;
        } else {
            parent = rnd.next(1, i - 1);
        }
        addEdge(edges, parent, i, profile);
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 16);
    } else if (mode == 1) {
        n = rnd.next(3, 22);
    } else {
        n = rnd.next(6, 30);
    }

    int profile = rnd.next(0, 4);
    vector<Edge> edges;
    if (mode == 0) {
        edges = makePath(n, profile);
    } else if (mode == 1) {
        edges = makeStar(n, profile);
    } else if (mode == 2) {
        edges = makeBinaryTree(n, profile);
    } else if (mode == 3) {
        edges = makeBroom(n, profile);
    } else {
        edges = makeRandomParentTree(n, profile);
    }

    vector<int> label(n + 1);
    label[1] = 1;
    vector<int> others;
    for (int i = 2; i <= n; ++i) {
        others.push_back(i);
    }
    shuffle(others.begin(), others.end());
    for (int i = 2; i <= n; ++i) {
        label[i] = others[i - 2];
    }

    shuffle(edges.begin(), edges.end());

    println(n);
    for (const Edge& edge : edges) {
        int a = label[edge.a];
        int b = label[edge.b];
        if (rnd.next(0, 1) == 1) {
            swap(a, b);
        }
        println(a, b, edge.w);
    }

    return 0;
}
