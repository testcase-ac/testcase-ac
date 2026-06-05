#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 18);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(19, 40);
    }

    vector<int> parent(n, -1);
    parent[0] = 0;

    if (mode == 0) {
        for (int v = 1; v < n; ++v) {
            parent[v] = v - 1;
        }
    } else if (mode == 1) {
        for (int v = 1; v < n; ++v) {
            parent[v] = 0;
        }
    } else if (mode == 2) {
        for (int v = 1; v < n; ++v) {
            parent[v] = (v - 1) / 2;
        }
    } else if (mode == 3) {
        int spine = rnd.next(1, n - 1);
        for (int v = 1; v <= spine; ++v) {
            parent[v] = v - 1;
        }
        for (int v = spine + 1; v < n; ++v) {
            parent[v] = rnd.next(0, spine);
        }
    } else {
        for (int v = 1; v < n; ++v) {
            parent[v] = rnd.next(0, v - 1);
        }
    }

    vector<int> values(n);
    iota(values.begin(), values.end(), 0);
    shuffle(values.begin(), values.end());

    int targetVertex;
    if (rnd.next(0, 4) == 0) {
        targetVertex = 0;
    } else if (rnd.next(0, 4) == 0) {
        targetVertex = n - 1;
    } else {
        targetVertex = rnd.next(0, n - 1);
    }
    int k = values[targetVertex];

    vector<pair<int, int>> edges;
    for (int v = 1; v < n; ++v) {
        edges.push_back({parent[v], v});
    }
    shuffle(edges.begin(), edges.end());

    println(n, k);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    println(values);

    return 0;
}
