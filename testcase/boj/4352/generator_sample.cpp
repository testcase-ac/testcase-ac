#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

static int randomLength(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(900000, 1000000);
    return rnd.next(1, 1000000);
}

static void maybeFlip(Edge& e) {
    if (rnd.next(2) == 0) swap(e.a, e.b);
}

static vector<Edge> makeCase(int active, int mode) {
    vector<Edge> edges;

    if (active == 1) {
        int loops = rnd.next(1, 4);
        for (int i = 0; i < loops; ++i) {
            edges.push_back({1, 1, randomLength(mode % 3)});
        }
        return edges;
    }

    for (int v = 2; v <= active; ++v) {
        int parent = mode == 0 ? v - 1 : rnd.next(1, v - 1);
        edges.push_back({parent, v, randomLength(mode % 3)});
    }

    if (mode == 1 && active >= 3) {
        edges.push_back({active, 1, randomLength(0)});
    }

    int extra = 0;
    if (mode == 2) {
        extra = rnd.next(active, active * 2);
    } else if (mode == 3) {
        extra = rnd.next(1, active + 3);
    } else {
        extra = rnd.next(0, active);
    }

    for (int i = 0; i < extra; ++i) {
        int a = rnd.next(1, active);
        int b = rnd.next(1, active);
        if (mode != 3 && a == b) {
            b = a % active + 1;
        }
        edges.push_back({a, b, randomLength((mode + i) % 3)});
    }

    if (mode == 2 && active >= 2) {
        int a = rnd.next(1, active - 1);
        int b = rnd.next(a + 1, active);
        int copies = rnd.next(2, 5);
        for (int i = 0; i < copies; ++i) {
            edges.push_back({a, b, randomLength(i % 3)});
        }
    }

    shuffle(edges.begin(), edges.end());
    for (Edge& e : edges) maybeFlip(e);
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 6);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = (tc + rnd.next(4)) % 4;
        int n;
        if (tc == 0) {
            n = rnd.next(1, 3);
        } else if (tc + 1 == cases) {
            n = rnd.next(10, 15);
        } else {
            n = rnd.next(4, 9);
        }

        int active = rnd.next(1, n);
        vector<Edge> edges = makeCase(active, mode);

        println(n, static_cast<int>(edges.size()));
        for (const Edge& e : edges) {
            println(e.a, e.b, e.w);
        }
    }

    println(0);
    return 0;
}
