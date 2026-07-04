#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Edge {
    int s;
    int e;
    int c;
    int a;
};

int chooseCost(int mode) {
    if (mode == 0) {
        return rnd.next(-30, 30);
    }
    if (mode == 1) {
        return rnd.next(-1000, 1000);
    }
    if (mode == 2) {
        return rnd.any(vector<int>{-100000000, -1000000, -1, 0, 1, 1000000, 100000000});
    }
    return rnd.next(-200000, 200000);
}

int chooseDelta(int mode) {
    if (mode == 0) {
        return rnd.next(-5, 5);
    }
    if (mode == 1) {
        return rnd.next(-1000, 1000);
    }
    if (mode == 2) {
        return rnd.any(vector<int>{-1000, -100, -1, 0, 1, 100, 1000});
    }
    return rnd.next(-50, 50);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 4);
    int n;
    if (shape == 0) {
        n = rnd.next(1, 3);
    } else if (shape == 1) {
        n = rnd.next(4, 9);
    } else {
        n = rnd.next(10, 25);
    }

    int dayMode = rnd.next(0, 5);
    int d;
    if (dayMode == 0) {
        d = 0;
    } else if (dayMode == 1) {
        d = rnd.next(1, 20);
    } else if (dayMode == 2) {
        d = rnd.next(100, 5000);
    } else if (dayMode == 3) {
        d = rnd.next(900000, 1000000);
    } else {
        d = rnd.next(0, 1000000);
    }

    vector<Edge> edges;
    int valueMode = rnd.next(0, 3);
    for (int v = 2; v <= n; ++v) {
        int parent;
        if (shape == 0 || shape == 1) {
            parent = v - 1;
        } else if (shape == 2) {
            parent = 1;
        } else if (shape == 3) {
            parent = max(1, v / 2);
        } else {
            parent = rnd.next(1, v - 1);
        }
        edges.push_back({parent, v, chooseCost(valueMode), chooseDelta(valueMode)});
    }

    int relabelMode = rnd.next(0, 2);
    if (relabelMode != 0) {
        vector<int> label(n + 1);
        for (int i = 1; i <= n; ++i) {
            label[i] = i;
        }
        shuffle(label.begin() + 1, label.end());
        for (Edge& edge : edges) {
            edge.s = label[edge.s];
            edge.e = label[edge.e];
        }
    }

    for (Edge& edge : edges) {
        if (rnd.next(0, 1) == 1) {
            swap(edge.s, edge.e);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, d);
    for (const Edge& edge : edges) {
        println(edge.s, edge.e, edge.c, edge.a);
    }
    return 0;
}
