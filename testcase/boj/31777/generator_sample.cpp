#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

long long nextWeight(int pattern, int index) {
    if (pattern == 0) {
        return rnd.next(1, 12);
    }
    if (pattern == 1) {
        return rnd.next(1, 2) == 1 ? 1 : 1000000000LL;
    }
    if (pattern == 2) {
        return 2LL * rnd.next(1, 10) + index % 2;
    }
    if (pattern == 3) {
        return index == 0 ? 1000000000LL : rnd.next(1, 5);
    }
    return rnd.next(1, 1000);
}

vector<Edge> makeCase(int n, int shape, int pattern) {
    vector<Edge> edges;
    edges.reserve(n - 1);

    for (int v = 2; v <= n; ++v) {
        int u = 1;
        if (shape == 0) {
            u = v - 1;
        } else if (shape == 1) {
            u = 1;
        } else if (shape == 2) {
            u = v / 2;
        } else if (shape == 3) {
            int window = rnd.next(1, min(v - 1, 4));
            u = rnd.next(max(1, v - window), v - 1);
        } else {
            u = rnd.next(1, v - 1);
        }
        edges.push_back({u, v, nextWeight(pattern, static_cast<int>(edges.size()))});
    }

    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<vector<Edge>> cases;
    cases.reserve(t);

    int remaining = rnd.next(max(t * 2, 8), 30);
    for (int tc = 0; tc < t; ++tc) {
        int minLeft = 2 * (t - tc - 1);
        int maxN = min(14, remaining - minLeft);
        int n = tc == t - 1 ? remaining : rnd.next(2, maxN);
        remaining -= n;

        int shape = rnd.next(0, 4);
        int pattern = rnd.next(0, 4);
        cases.push_back(makeCase(n, shape, pattern));
    }

    println(t);
    for (const auto& edges : cases) {
        println(static_cast<int>(edges.size()) + 1);
        for (const Edge& edge : edges) {
            println(edge.u, edge.v, edge.w);
        }
    }

    return 0;
}
