#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    long long w;
};

vector<Edge> makePath(int n) {
    vector<Edge> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({i, i + 1, 0});
    }
    return edges;
}

vector<Edge> makeStar(int n) {
    vector<Edge> edges;
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            edges.push_back({center, i, 0});
        }
    }
    return edges;
}

vector<Edge> makeBroom(int n) {
    vector<Edge> edges;
    int handle = rnd.next(2, n);
    for (int i = 1; i < handle; ++i) {
        edges.push_back({i, i + 1, 0});
    }
    for (int i = handle + 1; i <= n; ++i) {
        edges.push_back({handle, i, 0});
    }
    return edges;
}

vector<Edge> makeBinaryLike(int n) {
    vector<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i / 2, i, 0});
    }
    return edges;
}

vector<Edge> makeRandomTree(int n) {
    vector<Edge> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({rnd.next(1, i - 1), i, 0});
    }
    return edges;
}

long long chooseWeight(int index, int edgeCount, int mode) {
    if (mode == 0) {
        return rnd.next(1, 20);
    }
    if (mode == 1) {
        return rnd.any(vector<long long>{1, 2, 3, 5, 8, 13, 21});
    }
    if (mode == 2) {
        return 1000000000LL - rnd.next(0, 30);
    }
    if (mode == 3) {
        return index + 1;
    }
    if (mode == 4) {
        return edgeCount - index;
    }
    return rnd.next(1, 1000) * 1000000LL;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode == 1) {
        n = rnd.next(3, 7);
    } else if (sizeMode == 2) {
        n = rnd.next(8, 14);
    } else if (sizeMode == 3) {
        n = rnd.next(15, 25);
    } else {
        n = rnd.next(26, 40);
    }

    int topology = rnd.next(0, 4);
    vector<Edge> edges;
    if (topology == 0) {
        edges = makePath(n);
    } else if (topology == 1) {
        edges = makeStar(n);
    } else if (topology == 2) {
        edges = makeBroom(n);
    } else if (topology == 3) {
        edges = makeBinaryLike(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> labels(n);
    for (int i = 0; i < n; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());

    int weightMode = rnd.next(0, 5);
    for (int i = 0; i < int(edges.size()); ++i) {
        edges[i].a = labels[edges[i].a - 1];
        edges[i].b = labels[edges[i].b - 1];
        edges[i].w = chooseWeight(i, int(edges.size()), weightMode);
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.w);
    }

    return 0;
}
