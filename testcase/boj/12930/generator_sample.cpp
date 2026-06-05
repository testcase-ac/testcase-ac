#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

struct Graph {
    int n;
    vector<string> w1, w2;

    explicit Graph(int n_) : n(n_), w1(n_, string(n_, '.')), w2(n_, string(n_, '.')) {}

    void addEdge(int u, int v, int a, int b) {
        w1[u][v] = w1[v][u] = char('0' + a);
        w2[u][v] = w2[v][u] = char('0' + b);
    }
};

int weightNear(int target) {
    int delta = rnd.next(-2, 2);
    int value = target + delta;
    if (value < 1) value = 1;
    if (value > 9) value = 9;
    return value;
}

void addRandomEdge(Graph& g, int u, int v, int style) {
    if (style == 0) {
        g.addEdge(u, v, rnd.next(1, 9), rnd.next(1, 9));
    } else if (style == 1) {
        g.addEdge(u, v, weightNear(1), weightNear(9));
    } else if (style == 2) {
        g.addEdge(u, v, weightNear(9), weightNear(1));
    } else {
        int base = rnd.next(1, 9);
        g.addEdge(u, v, base, base);
    }
}

Graph disconnectedCase() {
    int n = rnd.next(2, 8);
    Graph g(n);
    int style = rnd.next(0, 3);
    for (int u = 2; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (rnd.next(100) < 45) addRandomEdge(g, u, v, style);
        }
    }
    if (n > 2 && rnd.next(2) == 0) addRandomEdge(g, 0, rnd.next(2, n - 1), style);
    return g;
}

Graph pathCase() {
    int n = rnd.next(2, 12);
    Graph g(n);
    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i;
    shuffle(vertices.begin() + 2, vertices.end());
    vertices[0] = 0;
    vertices[1] = 1;

    int pathLen = rnd.next(1, n - 1);
    int style = rnd.next(0, 3);
    int prev = 0;
    for (int i = 0; i < pathLen - 1; ++i) {
        addRandomEdge(g, prev, vertices[i + 2], style);
        prev = vertices[i + 2];
    }
    addRandomEdge(g, prev, 1, style);

    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (g.w1[u][v] == '.' && rnd.next(100) < 18) addRandomEdge(g, u, v, rnd.next(0, 3));
        }
    }
    return g;
}

Graph randomCase(bool dense) {
    int n = rnd.next(dense ? 5 : 2, dense ? 14 : 12);
    Graph g(n);
    int probability = dense ? rnd.next(50, 85) : rnd.next(12, 35);
    int style = rnd.next(0, 3);
    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (rnd.next(100) < probability) addRandomEdge(g, u, v, style);
        }
    }
    return g;
}

Graph tradeoffCase() {
    int n = rnd.next(4, 10);
    Graph g(n);
    g.addEdge(0, 1, rnd.next(7, 9), rnd.next(7, 9));

    int a = 2, b = 3;
    g.addEdge(0, a, rnd.next(1, 3), rnd.next(7, 9));
    g.addEdge(a, 1, rnd.next(1, 3), rnd.next(7, 9));
    g.addEdge(0, b, rnd.next(7, 9), rnd.next(1, 3));
    g.addEdge(b, 1, rnd.next(7, 9), rnd.next(1, 3));

    for (int v = 4; v < n; ++v) {
        int anchor = rnd.next(0, v - 1);
        addRandomEdge(g, anchor, v, rnd.next(0, 3));
        if (rnd.next(2) == 0) addRandomEdge(g, v, rnd.next(0, v - 1), rnd.next(0, 3));
    }
    return g;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    Graph g = mode == 0 ? disconnectedCase()
              : mode == 1 ? pathCase()
              : mode == 2 ? randomCase(false)
              : mode == 3 ? randomCase(true)
                          : tradeoffCase();

    println(g.n);
    for (const string& row : g.w1) println(row);
    for (const string& row : g.w2) println(row);
    return 0;
}
