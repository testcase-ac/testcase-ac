#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, i + 1);
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) {
            edges.emplace_back(center, v);
        }
    }
    return edges;
}

vector<pair<int, int>> makeBinaryLike(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        edges.emplace_back(v / 2, v);
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int spine = rnd.next(2, max(2, n - 1));
    for (int i = 1; i < spine; ++i) {
        edges.emplace_back(i, i + 1);
    }
    int attach = rnd.next(1, spine);
    for (int v = spine + 1; v <= n; ++v) {
        edges.emplace_back(attach, v);
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = rnd.next(1, v - 1);
        edges.emplace_back(parent, v);
    }
    return edges;
}

void relabelAndPrint(int n, vector<pair<int, int>> edges) {
    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [u, v] : edges) {
        u = label[u];
        v = label[v];
        if (rnd.next(2) == 0) {
            swap(u, v);
        }
        println(u, v);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 9);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(5);
        int n = rnd.next(2, 15);
        if (caseIndex == 0 && rnd.next(2) == 0) {
            n = 15;
        }

        vector<pair<int, int>> edges;
        if (mode == 0) {
            edges = makePath(n);
        } else if (mode == 1) {
            edges = makeStar(n);
        } else if (mode == 2) {
            edges = makeBinaryLike(n);
        } else if (mode == 3) {
            edges = makeBroom(n);
        } else {
            edges = makeRandomTree(n);
        }

        relabelAndPrint(n, edges);
    }

    return 0;
}
