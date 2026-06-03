#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    long long d;
    long long t;
};

long long smallWeight() {
    return rnd.next(1, 12);
}

long long wideWeight() {
    if (rnd.next(5) == 0) {
        return rnd.next(100000000LL, 1000000000LL);
    }
    return smallWeight();
}

void maybeFlip(Edge& e) {
    if (rnd.next(2) == 0) {
        swap(e.u, e.v);
    }
}

void addEdge(vector<Edge>& edges, int u, int v, long long d, long long t) {
    Edge e{u, v, d, t};
    maybeFlip(e);
    edges.push_back(e);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    vector<Edge> edges;

    if (mode == 0) {
        long long now = rnd.next(0, 8);
        for (int i = 1; i < n; ++i) {
            long long d = smallWeight();
            now += d;
            long long slack = rnd.next(0, 10);
            addEdge(edges, i, i + 1, d, now + slack);
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            long long d = wideWeight();
            long long t = d + rnd.next(0, 30);
            addEdge(edges, 1, v, d, t);
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            int parent = rnd.next(1, v - 1);
            long long d = smallWeight();
            long long t = d + rnd.next(0, 40);
            addEdge(edges, parent, v, d, t);
        }

        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int extra = rnd.next(0, min<int>(20, candidates.size()));
        for (int i = 0; i < extra; ++i) {
            long long d = wideWeight();
            long long t = rnd.next(1, 60);
            addEdge(edges, candidates[i].first, candidates[i].second, d, t);
        }
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            long long d = rnd.next(1, 6);
            long long t = rnd.next(1, 18);
            addEdge(edges, i, i + 1, d, t);
        }

        int repeats = rnd.next(1, 8);
        for (int i = 0; i < repeats; ++i) {
            int u = rnd.next(1, n - 1);
            int v = rnd.next(u + 1, n);
            long long d = rnd.next(1, 10);
            long long t = rnd.next(d, d + 50);
            addEdge(edges, u, v, d, t);
        }
    } else {
        long long prefix = rnd.next(0, 20);
        for (int i = 1; i < n; ++i) {
            long long d = rnd.next(1, 9);
            prefix += d;
            long long t = (i == n - 1 && rnd.next(2) == 0) ? max(1LL, prefix - rnd.next(1, 5)) : prefix + rnd.next(0, 25);
            addEdge(edges, i, i + 1, d, t);
        }

        int shortcuts = rnd.next(0, min(10, n * (n - 1) / 2));
        for (int i = 0; i < shortcuts; ++i) {
            int u = rnd.next(1, n - 1);
            int v = rnd.next(u + 1, n);
            long long d = rnd.next(1, 20);
            long long t = rnd.next(1, 80);
            addEdge(edges, u, v, d, t);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    for (const Edge& e : edges) {
        println(e.u, e.v, e.d, e.t);
    }

    return 0;
}
