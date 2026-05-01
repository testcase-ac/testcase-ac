#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(10, 30);
    int max_w = 3;

    vector<Edge> edges;
    for (int v = 1; v < n; v++) {
        int u = rnd.next(v);
        int w = rnd.wnext(0, max_w, -1);
        edges.emplace_back(u, v, w);
    }

    shuffle(edges.begin(), edges.end());

    double k_float = 0;
    for (auto [_1, _2, w] : edges) { k_float += w; }
    k_float /= rnd.next(2.0, 3.0);

    int k = max(1, int(k_float));

    println(n, k);
    for (auto [u, v, w] : edges) {
        if (rnd.next(2)) { swap(u, v); }
        println(u, v, w);
    }

    return 0;
}
