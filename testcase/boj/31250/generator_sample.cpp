#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

const long long MAX_VALUE = 1000000000000000000LL;

struct Edge {
    int u;
    int v;
    long long b;
};

long long randomValue(int mode) {
    if (mode == 0) return rnd.next(0LL, 20LL);
    if (mode == 1) return rnd.next(0LL, 1000000LL);
    if (mode == 2) return MAX_VALUE - rnd.next(0LL, 1000LL);
    return rnd.next(0LL, MAX_VALUE);
}

void addEdge(vector<Edge>& edges, set<long long>& usedB, int u, int v, long long b) {
    for (long long delta = 0; ; ++delta) {
        if (b + delta <= MAX_VALUE && !usedB.count(b + delta)) {
            b += delta;
            break;
        }
        if (b - delta >= 0 && !usedB.count(b - delta)) {
            b -= delta;
            break;
        }
    }
    usedB.insert(b);
    edges.push_back({u, v, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 2 ? 14 : 9);
    int mTarget = rnd.next(1, mode == 2 ? 40 : 24);
    long long k;

    if (mode == 3) {
        k = MAX_VALUE - rnd.next(0LL, 10000LL);
    } else if (mode == 4) {
        k = rnd.next(1000LL, 1000000LL);
    } else {
        k = rnd.next(1LL, 200LL);
    }

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (mode == 1 && rnd.next(0, 3) == 0) {
            a[i] = 0;
        } else if (mode == 3 && rnd.next(0, 4) == 0) {
            a[i] = MAX_VALUE - rnd.next(0LL, 1000LL);
        } else {
            a[i] = rnd.next(0LL, mode == 4 ? 1000LL : 30LL);
        }
    }

    if (mode == 4) {
        a[rnd.next(1, n)] = 0;
    }

    vector<Edge> edges;
    set<long long> usedB;

    if (mode == 0) {
        for (int i = 1; i <= n && (int)edges.size() < mTarget; ++i) {
            int v = i == n ? 1 : i + 1;
            addEdge(edges, usedB, i, v, rnd.next(0LL, 60LL));
        }
    } else if (mode == 1) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) ++v;
        int duplicates = min(mTarget, rnd.next(2, 8));
        for (int i = 0; i < duplicates; ++i) {
            addEdge(edges, usedB, u, v, rnd.next(0LL, 80LL));
        }
    } else if (mode == 2) {
        for (int i = 0; i < min(mTarget, n * 2); ++i) {
            int u = i % n + 1;
            int v = (i + 1) % n + 1;
            if (u == v) v = v % n + 1;
            addEdge(edges, usedB, u, v, rnd.next(0LL, 200LL));
        }
    } else if (mode == 3) {
        addEdge(edges, usedB, 1, rnd.next(2, n), MAX_VALUE);
        while ((int)edges.size() < min(mTarget, n + 4)) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(edges, usedB, u, v, MAX_VALUE - rnd.next(0LL, 100000LL));
        }
    } else {
        int hub = rnd.next(1, n);
        for (int v = 1; v <= n && (int)edges.size() < mTarget; ++v) {
            if (v == hub) continue;
            addEdge(edges, usedB, hub, v, rnd.next(0LL, 2000LL));
        }
    }

    while ((int)edges.size() < mTarget) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) ++v;
        addEdge(edges, usedB, u, v, randomValue(mode == 3 ? 2 : rnd.next(0, 3)));
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), k);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) printf(" ");
        printf("%lld", a[i]);
    }
    printf("\n");
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.b);
    }

    return 0;
}
