#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int d;
};

int nextWeight(int mode) {
    if (mode == 0) {
        return rnd.next(1, 10);
    }
    if (mode == 1) {
        return rnd.next(99990, 100000);
    }
    if (mode == 2) {
        return rnd.any(vector<int>{1, 2, 3, 99998, 99999, 100000});
    }
    return rnd.next(1, 100000);
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int d) {
    if (a > b) {
        swap(a, b);
    }
    if (used.insert({a, b}).second) {
        edges.push_back({a, b, d});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 15);
    int cMode = rnd.next(0, 3);
    int weightMode = rnd.next(0, 3);

    int c = 1;
    if (cMode == 0) {
        c = rnd.next(1, 12);
    } else if (cMode == 1) {
        c = rnd.next(99990, 100000);
    } else {
        c = rnd.any(vector<int>{1, 2, 10, 100, 99999, 100000});
    }

    vector<Edge> edges;
    set<pair<int, int>> used;

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end());

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, vertices[i - 1], vertices[i], nextWeight(weightMode));
        }
    } else if (mode == 1) {
        int center = vertices[0];
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, center, vertices[i], nextWeight(weightMode));
        }
    } else {
        for (int i = 1; i < n; ++i) {
            int parent = vertices[rnd.next(0, i - 1)];
            addEdge(edges, used, parent, vertices[i], nextWeight(weightMode));
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = static_cast<int>(candidates.size());
    int extra = 0;
    if (mode == 2) {
        extra = rnd.next(0, min(extraLimit, n));
    } else if (mode == 3) {
        extra = rnd.next(extraLimit / 2, extraLimit);
    } else if (mode == 4) {
        extra = rnd.next(0, extraLimit);
    }

    for (int i = 0; i < extra; ++i) {
        addEdge(edges, used, candidates[i].first, candidates[i].second, nextWeight(weightMode));
    }

    for (Edge& edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.a, edge.b);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), c);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.d);
    }

    return 0;
}
