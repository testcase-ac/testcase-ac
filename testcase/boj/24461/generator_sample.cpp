#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(vector<pair<int, int>>& edges, int a, int b) {
    edges.emplace_back(a, b);
}

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        addEdge(edges, i - 1, i);
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(0, n - 1);
    for (int i = 0; i < n; ++i) {
        if (i != center) {
            addEdge(edges, center, i);
        }
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int pathLen = rnd.next(2, max(2, n - 1));
    for (int i = 1; i < pathLen; ++i) {
        addEdge(edges, i - 1, i);
    }
    int hub = rnd.next(0, pathLen - 1);
    for (int i = pathLen; i < n; ++i) {
        addEdge(edges, hub, i);
    }
    return edges;
}

vector<pair<int, int>> makeDoubleHub(int n) {
    vector<pair<int, int>> edges;
    addEdge(edges, 0, 1);
    for (int i = 2; i < n; ++i) {
        addEdge(edges, rnd.next(0, 1), i);
    }
    return edges;
}

vector<pair<int, int>> makeBalanced(int n) {
    vector<pair<int, int>> edges;
    int maxChildren = rnd.next(2, 4);
    for (int i = 1; i < n; ++i) {
        int parent = (i - 1) / maxChildren;
        addEdge(edges, parent, i);
    }
    return edges;
}

vector<pair<int, int>> makeCaterpillar(int n) {
    vector<pair<int, int>> edges;
    int spine = rnd.next(2, max(2, min(n, 8)));
    for (int i = 1; i < spine; ++i) {
        addEdge(edges, i - 1, i);
    }
    for (int i = spine; i < n; ++i) {
        addEdge(edges, rnd.next(0, spine - 1), i);
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<int> degree(n, 1);
    vector<int> prufer;
    for (int i = 0; i < n - 2; ++i) {
        int v = rnd.next(0, n - 1);
        prufer.push_back(v);
        ++degree[v];
    }

    set<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            leaves.insert(i);
        }
    }

    vector<pair<int, int>> edges;
    for (int v : prufer) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
        addEdge(edges, leaf, v);
        if (--degree[v] == 1) {
            leaves.insert(v);
        }
    }
    addEdge(edges, *leaves.begin(), *next(leaves.begin()));
    return edges;
}

int chooseN(int mode) {
    if (mode == 0) {
        return rnd.next(2, 14);
    }
    if (mode == 1) {
        return rnd.next(3, 14);
    }
    if (mode == 2 || mode == 5) {
        return rnd.next(4, 16);
    }
    if (mode == 3) {
        return rnd.next(4, 18);
    }
    if (mode == 4) {
        return rnd.next(7, 20);
    }
    return rnd.next(2, 18);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = chooseN(mode);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges = makePath(n);
    } else if (mode == 1) {
        edges = makeStar(n);
    } else if (mode == 2) {
        edges = makeBroom(n);
    } else if (mode == 3) {
        edges = makeDoubleHub(n);
    } else if (mode == 4) {
        edges = makeBalanced(n);
    } else if (mode == 5) {
        edges = makeCaterpillar(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> label(n);
    for (int i = 0; i < n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin(), label.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [a, b] : edges) {
        a = label[a];
        b = label[b];
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}
