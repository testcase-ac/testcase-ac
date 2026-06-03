#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

Edge normalizeEdge(int a, int b) {
    if (a > b) swap(a, b);
    return {a, b};
}

void addEdge(vector<Edge>& edges, int a, int b) {
    edges.push_back(normalizeEdge(a, b));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<Edge> edges;

    if (mode == 0) {
        int m = rnd.next(1, min(60, n * 3));
        for (int i = 0; i < m; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            addEdge(edges, a, b);
        }
    } else if (mode == 1) {
        vector<Edge> all;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                all.push_back({a, b});
            }
        }
        shuffle(all.begin(), all.end());

        int uniqueCount = rnd.next(1, min<int>(all.size(), 20));
        for (int i = 0; i < uniqueCount; ++i) {
            edges.push_back(all[i]);
        }

        int duplicateCount = rnd.next(0, uniqueCount + 8);
        for (int i = 0; i < duplicateCount; ++i) {
            edges.push_back(rnd.any(edges));
        }
        shuffle(edges.begin(), edges.end());
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            if (rnd.next(0, 99) < 75) {
                addEdge(edges, 1, v);
            }
        }
        if (edges.empty()) {
            addEdge(edges, 1, rnd.next(2, n));
        }

        int extras = rnd.next(0, min(20, n));
        for (int i = 0; i < extras; ++i) {
            int a = rnd.next(2, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            addEdge(edges, a, b);
        }
        shuffle(edges.begin(), edges.end());
    } else if (mode == 3) {
        int leftSize = rnd.next(1, n - 1);
        vector<int> vertices;
        for (int i = 1; i <= n; ++i) {
            vertices.push_back(i);
        }
        shuffle(vertices.begin(), vertices.end());

        vector<int> left(vertices.begin(), vertices.begin() + leftSize);
        vector<int> right(vertices.begin() + leftSize, vertices.end());
        for (int a : left) {
            for (int b : right) {
                addEdge(edges, a, b);
            }
        }
        if (rnd.next(0, 1)) {
            edges.push_back(rnd.any(edges));
        }
        shuffle(edges.begin(), edges.end());
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        vector<Edge> all;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                all.push_back({a, b});
            }
        }
        shuffle(all.begin(), all.end());

        int uniqueCount = rnd.next(1, static_cast<int>(all.size()));
        edges.assign(all.begin(), all.begin() + uniqueCount);
        shuffle(edges.begin(), edges.end());
    } else {
        n = rnd.next(2, 6);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        int m = rnd.next(1, 30);
        for (int i = 0; i < m; ++i) {
            addEdge(edges, a, b);
        }
    }

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
