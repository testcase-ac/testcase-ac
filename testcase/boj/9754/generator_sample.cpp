#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

vector<Edge> makePath(int n) {
    vector<Edge> edges;
    for (int v = 2; v <= n; ++v) {
        edges.push_back({v - 1, v});
    }
    return edges;
}

vector<Edge> makeStar(int n) {
    vector<Edge> edges;
    int center = rnd.next(1, n);
    for (int v = 1; v <= n; ++v) {
        if (v != center) {
            edges.push_back({center, v});
        }
    }
    return edges;
}

vector<Edge> makeBinaryTree(int n) {
    vector<Edge> edges;
    for (int v = 2; v <= n; ++v) {
        edges.push_back({v / 2, v});
    }
    return edges;
}

vector<Edge> makeRandomTree(int n) {
    vector<Edge> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = rnd.next(1, v - 1);
        edges.push_back({parent, v});
    }
    return edges;
}

void relabelAndPrint(int n, vector<Edge> edges) {
    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    for (auto [a, b] : edges) {
        a = label[a];
        b = label[b];
        if (rnd.next(0, 1) == 1) {
            swap(a, b);
        }
        println(a, b);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (mode == 0) {
            n = rnd.next(2, 12);
        } else if (mode == 1) {
            n = rnd.next(3, 25);
        } else if (mode == 2) {
            n = rnd.next(7, 40);
        } else if (mode == 3) {
            n = rnd.next(2, 60);
        } else {
            n = rnd.next(80, 200);
        }

        int k;
        if (tc == 0) {
            k = 1;
        } else if (tc == 1) {
            k = 2;
        } else if (tc == 2) {
            k = 10;
        } else {
            k = rnd.next(1, 10);
        }

        vector<Edge> edges;
        if (mode == 0) {
            edges = makePath(n);
        } else if (mode == 1) {
            edges = makeStar(n);
        } else if (mode == 2) {
            edges = makeBinaryTree(n);
        } else {
            edges = makeRandomTree(n);
        }

        println(n, k);
        relabelAndPrint(n, edges);
    }

    return 0;
}
