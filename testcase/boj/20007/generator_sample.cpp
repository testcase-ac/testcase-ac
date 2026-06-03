#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int c) {
    if (a > b) swap(a, b);
    if (used.insert({a, b}).second) {
        edges.push_back({a, b, c});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, mode == 4 ? 14 : 10);
    int y = rnd.next(0, n - 1);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        vector<int> order;
        for (int i = 0; i < n; ++i) {
            if (i != y) order.push_back(i);
        }
        shuffle(order.begin(), order.end());

        int prev = y;
        for (int v : order) {
            addEdge(edges, used, prev, v, rnd.next(1, 12));
            prev = v;
        }
    } else if (mode == 1) {
        for (int v = 0; v < n; ++v) {
            if (v != y) addEdge(edges, used, y, v, rnd.next(1, 25));
        }
    } else if (mode == 2) {
        int connected = rnd.next(1, n - 1);
        vector<int> vertices;
        for (int i = 0; i < n; ++i) vertices.push_back(i);
        shuffle(vertices.begin(), vertices.end());

        vector<int> near = {y};
        for (int v : vertices) {
            if (v != y && (int)near.size() < connected) near.push_back(v);
        }

        for (int i = 1; i < (int)near.size(); ++i) {
            int parent = near[rnd.next(i)];
            addEdge(edges, used, parent, near[i], rnd.next(1, 20));
        }

        vector<int> far;
        for (int v = 0; v < n; ++v) {
            if (find(near.begin(), near.end(), v) == near.end()) far.push_back(v);
        }
        for (int i = 1; i < (int)far.size(); ++i) {
            addEdge(edges, used, far[i - 1], far[i], rnd.next(1, 20));
        }
    } else {
        vector<int> order;
        for (int i = 0; i < n; ++i) {
            if (i != y) order.push_back(i);
        }
        shuffle(order.begin(), order.end());

        for (int i = 0; i < (int)order.size(); ++i) {
            int parent = (i == 0 || rnd.next(2) == 0) ? y : order[rnd.next(i)];
            int weight = (mode == 3) ? rnd.next(20, 70) : rnd.next(1, 40);
            addEdge(edges, used, parent, order[i], weight);
        }
    }

    double extraProb = (mode == 4) ? rnd.next(0.35, 0.75) : rnd.next(0.05, 0.25);
    for (int a = 0; a < n; ++a) {
        for (int b = a + 1; b < n; ++b) {
            if (!used.count({a, b}) && rnd.next() < extraProb) {
                int weight = rnd.next(1, mode == 3 ? 90 : 60);
                addEdge(edges, used, a, b, weight);
            }
        }
    }

    if (edges.empty()) {
        int other = (y == 0 ? 1 : 0);
        addEdge(edges, used, y, other, rnd.next(1, 30));
    }

    int x;
    if (mode == 2) {
        x = rnd.next(1, 120);
    } else if (mode == 3) {
        x = rnd.next(40, 180);
    } else if (rnd.next(3) == 0) {
        x = rnd.next(1, 20);
    } else {
        x = rnd.next(30, 250);
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), x, y);
    for (const Edge& edge : edges) {
        if (rnd.next(2) == 0) {
            println(edge.a, edge.b, edge.c);
        } else {
            println(edge.b, edge.a, edge.c);
        }
    }

    return 0;
}
