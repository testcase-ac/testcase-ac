#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(4, 14);
    }

    vector<tuple<int, int, int>> edges;
    auto addEdge = [&](int u, int v, int w) {
        edges.emplace_back(u, v, w);
    };
    auto weight = [&]() {
        int style = rnd.next(0, 4);
        if (style == 0) {
            return 1;
        }
        if (style == 1) {
            return rnd.next(2, 20);
        }
        if (style == 2) {
            return rnd.next(21, 1000);
        }
        if (style == 3) {
            return 1000000000;
        }
        return rnd.next(999999900, 1000000000);
    };

    if (n == 1) {
        addEdge(1, 1, weight());
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            addEdge(1, v, weight());
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            addEdge(v - 1, v, weight());
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            addEdge(rnd.next(1, v - 1), v, weight());
        }
    }

    int maxM = min(45, 250000);
    int extra = rnd.next(0, max(0, maxM - static_cast<int>(edges.size())));
    if (mode == 2) {
        extra = rnd.next(0, min(4, max(0, maxM - static_cast<int>(edges.size()))));
    }

    for (int i = 0; i < extra; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        if (mode == 3 && rnd.next(0, 2) == 0) {
            v = u;
        }
        if (mode == 4 && !edges.empty() && rnd.next(0, 3) == 0) {
            auto [a, b, oldW] = rnd.any(edges);
            (void)oldW;
            u = a;
            v = b;
        }
        addEdge(u, v, weight());
    }

    shuffle(edges.begin(), edges.end());

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    int k;
    if (mode == 5) {
        k = n;
    } else if (n == 1) {
        k = 1;
    } else {
        k = rnd.next(1, n);
    }
    vertices.resize(k);
    sort(vertices.begin(), vertices.end());

    println(n, static_cast<int>(edges.size()));
    for (auto [u, v, w] : edges) {
        println(u, v, w);
    }
    println(k);
    println(vertices);

    return 0;
}
