#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else {
        n = rnd.next(5, 12);
    }

    int maxEdges = min(28, n * n);
    int m = rnd.next(1, maxEdges);
    int p = rnd.next(1, 10);

    int k;
    if (mode == 0) {
        k = 0;
    } else if (mode == 2) {
        k = rnd.next(0, min(n - 1, 2));
    } else if (mode == 3) {
        k = rnd.next(max(0, n / 2 - 1), n - 1);
    } else {
        k = rnd.next(0, n - 1);
    }

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    vector<int> traps(vertices.begin(), vertices.begin() + k);
    sort(traps.begin(), traps.end());

    vector<bool> isTrap(n + 1, false);
    for (int x : traps) {
        isTrap[x] = true;
    }

    vector<int> starts;
    for (int x = 1; x <= n; ++x) {
        if (!isTrap[x]) {
            starts.push_back(x);
        }
    }
    int s = rnd.any(starts);
    int e = rnd.next(1, n);

    vector<Edge> edges;
    edges.reserve(m);

    auto addEdge = [&](int a, int b, int c) {
        edges.push_back({a, b, c});
    };

    if (mode != 0 && rnd.next(0, 1)) {
        addEdge(s, e, rnd.next(1, 20));
    }

    while ((int)edges.size() < m) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);

        if (mode == 1 && rnd.next(0, 3) > 0) {
            b = rnd.next(1, n);
            while (b == a && n > 1) {
                b = rnd.next(1, n);
            }
        }
        if (mode == 4 && rnd.next(0, 4) == 0) {
            b = a;
        }

        int c;
        if (mode == 5 && rnd.next(0, 3) == 0) {
            c = rnd.next(1000, 10000);
        } else {
            c = rnd.next(1, 50);
        }
        addEdge(a, b, c);
    }

    int l;
    if (m == 1) {
        l = rnd.next(0, 1);
    } else if (mode == 0) {
        l = rnd.next(0, m);
    } else if (mode == 2) {
        l = rnd.next(1, m);
    } else {
        l = rnd.next(0, m);
    }

    shuffle(edges.begin(), edges.end());
    vector<Edge> trapEdges(edges.begin(), edges.begin() + l);
    vector<Edge> normalEdges(edges.begin() + l, edges.end());

    println(n, m, k, l, p);
    println(traps);
    for (const Edge& edge : normalEdges) {
        println(edge.a, edge.b, edge.c);
    }
    for (const Edge& edge : trapEdges) {
        println(edge.a, edge.b, edge.c);
    }
    println(s, e);

    return 0;
}
