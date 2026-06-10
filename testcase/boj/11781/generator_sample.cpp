#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    long long len;
    int t1;
    int t2;
};

long long chooseLength(int mode) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.next(1, 80);
    if (mode == 2) return rnd.any(vector<long long>{1, 2, 3, 999999999LL, 1000000000LL});
    return rnd.next(1, 1000000000);
}

pair<int, int> chooseFlags(int mode) {
    if (mode == 0) return {0, 0};
    if (mode == 1) return {1, 1};
    if (mode == 2) return rnd.any(vector<pair<int, int>>{{1, 0}, {0, 1}});
    return {rnd.next(0, 1), rnd.next(0, 1)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int shape = rnd.next(0, 5);
    int timeMode = rnd.next(0, 4);

    long long s;
    long long e;
    if (timeMode == 0) {
        s = 0;
        e = rnd.next(1, 20);
    } else if (timeMode == 1) {
        s = rnd.next(1, 20);
        e = s + rnd.next(1, 20);
    } else if (timeMode == 2) {
        s = rnd.next(999999900, 999999999);
        e = 1000000000LL;
    } else if (timeMode == 3) {
        s = rnd.next(0, 5);
        e = s + 1;
    } else {
        s = rnd.next(0, 1000);
        e = rnd.next(s + 1, s + 1000);
    }

    vector<Edge> edges;
    auto addEdge = [&](int a, int b, int lengthMode, int flagMode) {
        pair<int, int> flags = chooseFlags(flagMode);
        edges.push_back({a, b, chooseLength(lengthMode), flags.first, flags.second});
    };

    if (shape == 0) {
        for (int v = 2; v <= n; ++v) addEdge(v - 1, v, rnd.next(0, 2), rnd.next(0, 3));
    } else if (shape == 1) {
        for (int v = 2; v <= n; ++v) addEdge(1, v, rnd.next(0, 2), rnd.next(0, 3));
    } else {
        vector<int> order;
        for (int v = 1; v <= n; ++v) order.push_back(v);
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(parent, order[i], rnd.next(0, 2), rnd.next(0, 3));
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) candidates.push_back({a, b});
    }
    shuffle(candidates.begin(), candidates.end());

    int extra = rnd.next(0, min<int>(candidates.size(), n + 4));
    for (int i = 0; i < extra; ++i) {
        pair<int, int> p = candidates[i];
        if (rnd.next(0, 1)) swap(p.first, p.second);
        addEdge(p.first, p.second, rnd.next(0, 3), rnd.next(0, 3));
    }

    if (rnd.next(0, 4) == 0) {
        Edge base = rnd.any(edges);
        addEdge(base.a, base.b, rnd.next(0, 3), rnd.next(0, 3));
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), s, e);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.len, edge.t1, edge.t2);
    }

    return 0;
}
