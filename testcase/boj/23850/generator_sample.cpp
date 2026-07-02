#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 24);
    int mode = rnd.next(0, 4);
    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    vector<pair<int, int>> edges;

    auto find = [&](int v) {
        while (parent[v] != v) {
            parent[v] = parent[parent[v]];
            v = parent[v];
        }
        return v;
    };

    auto unite = [&](int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) {
            return false;
        }
        parent[rb] = ra;
        edges.push_back({a, b});
        return true;
    };

    if (mode == 0) {
        // Many isolated vertices, plus a few short links.
        int target = rnd.next(0, max(0, n / 3));
        while ((int)edges.size() < target) {
            unite(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 1) {
        // One long path, optionally with isolated vertices after it.
        int len = rnd.next(1, n);
        vector<int> vertices(n);
        iota(vertices.begin(), vertices.end(), 1);
        shuffle(vertices.begin(), vertices.end());
        for (int i = 1; i < len; ++i) {
            unite(vertices[i - 1], vertices[i]);
        }
    } else if (mode == 2) {
        // A star-like component stresses high-degree centers.
        int center = rnd.next(1, n);
        vector<int> leaves;
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                leaves.push_back(v);
            }
        }
        shuffle(leaves.begin(), leaves.end());
        int leafCount = rnd.next(0, (int)leaves.size());
        for (int i = 0; i < leafCount; ++i) {
            unite(center, leaves[i]);
        }
    } else {
        // Random forest with several components and mixed local shapes.
        int target = rnd.next(0, n - 1);
        int attempts = 0;
        while ((int)edges.size() < target && attempts < 8 * n) {
            ++attempts;
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (a != b) {
                unite(a, b);
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}
