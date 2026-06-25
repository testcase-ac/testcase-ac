#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(vector<pair<int, int>>& edges, int a, int b) {
    if (rnd.next(2) == 0) {
        swap(a, b);
    }
    edges.emplace_back(a, b);
}

static vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        addEdge(edges, i - 1, i);
    }
    return edges;
}

static vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            addEdge(edges, center, i);
        }
    }
    return edges;
}

static vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, n);
    for (int i = 2; i <= handle; ++i) {
        addEdge(edges, i - 1, i);
    }
    for (int i = handle + 1; i <= n; ++i) {
        addEdge(edges, handle, i);
    }
    return edges;
}

static vector<pair<int, int>> makeBinaryLike(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        addEdge(edges, i / 2, i);
    }
    return edges;
}

static vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    int bias = rnd.next(4);
    for (int i = 2; i <= n; ++i) {
        int parent;
        if (bias == 0) {
            parent = rnd.next(1, i - 1);
        } else if (bias == 1) {
            parent = max(1, i - rnd.next(1, min(i - 1, 5)));
        } else if (bias == 2) {
            parent = rnd.wnext(i - 1, -2) + 1;
        } else {
            parent = rnd.wnext(i - 1, 2) + 1;
        }
        addEdge(edges, parent, i);
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (rnd.next(8) == 0) {
        n = rnd.next(2, 120);
    } else {
        n = rnd.next(2, 35);
    }

    int lMode = rnd.next(5);
    int l;
    if (lMode == 0) {
        l = 0;
    } else if (lMode == 1) {
        l = n;
    } else if (lMode == 2) {
        l = rnd.next(0, min(n, 5));
    } else if (lMode == 3) {
        l = rnd.next(max(0, n - 5), n);
    } else {
        l = rnd.next(0, n);
    }

    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges = makePath(n);
    } else if (mode == 1) {
        edges = makeStar(n);
    } else if (mode == 2) {
        edges = makeBroom(n);
    } else if (mode == 3) {
        edges = makeBinaryLike(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n, l);
    for (const auto& edge : edges) {
        println(label[edge.first], label[edge.second]);
    }

    return 0;
}
