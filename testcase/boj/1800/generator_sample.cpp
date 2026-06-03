#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& seen, int a, int b, int w) {
    if (a == b) return;
    pair<int, int> key = minmax(a, b);
    if (!seen.insert(key).second) return;
    edges.push_back({a, b, w});
}

static int weightFromBand(int band) {
    if (band == 0) return rnd.next(1, 12);
    if (band == 1) return rnd.next(13, 200);
    return rnd.next(201, 1000000);
}

static void relabelAndPrint(int n, int k, vector<Edge> edges) {
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) perm[i] = i;

    vector<int> middle;
    for (int i = 2; i < n; ++i) middle.push_back(i);
    shuffle(middle.begin(), middle.end());
    for (int i = 2; i < n; ++i) perm[i] = middle[i - 2];

    for (Edge& e : edges) {
        e.a = perm[e.a];
        e.b = perm[e.b];
        if (rnd.next(2)) swap(e.a, e.b);
    }
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), k);
    for (const Edge& e : edges) println(e.a, e.b, e.w);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    int k = rnd.next(0, n - 1);
    vector<Edge> edges;
    set<pair<int, int>> seen;

    if (mode == 0) {
        int leftSize = rnd.next(1, n - 1);
        if (leftSize == n - 1 && rnd.next(2)) leftSize = 1;
        for (int i = 1; i <= leftSize; ++i) {
            for (int j = i + 1; j <= leftSize; ++j) {
                if (rnd.next() < 0.45) addEdge(edges, seen, i, j, weightFromBand(rnd.next(3)));
            }
        }
        for (int i = leftSize + 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < 0.45) addEdge(edges, seen, i, j, weightFromBand(rnd.next(3)));
            }
        }
        if (edges.empty()) addEdge(edges, seen, 1, min(2, n), weightFromBand(0));
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) addEdge(edges, seen, i, i + 1, weightFromBand(i % 3));
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 2; j <= n; ++j) {
                if (rnd.next() < 0.18) addEdge(edges, seen, i, j, weightFromBand(rnd.next(3)));
            }
        }
        k = rnd.next(0, n - 1);
    } else if (mode == 2) {
        double density = rnd.next(0.35, 0.85);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if ((i == 1 && j == n) || rnd.next() < density) {
                    addEdge(edges, seen, i, j, weightFromBand(rnd.next(3)));
                }
            }
        }
    } else if (mode == 3) {
        n = rnd.next(5, 14);
        int split = rnd.next(3, n - 1);
        addEdge(edges, seen, 1, 2, rnd.next(1, 20));
        for (int i = 2; i < split; ++i) addEdge(edges, seen, i, i + 1, rnd.next(500000, 1000000));
        addEdge(edges, seen, split, n, rnd.next(1, 20));

        int cur = split + 1;
        addEdge(edges, seen, 1, cur, rnd.next(50, 200));
        while (cur + 1 < n) {
            addEdge(edges, seen, cur, cur + 1, rnd.next(50, 200));
            ++cur;
        }
        addEdge(edges, seen, cur, n, rnd.next(50, 200));

        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < 0.08) addEdge(edges, seen, i, j, weightFromBand(rnd.next(3)));
            }
        }
        k = rnd.next(0, min(n - 1, 5));
    } else {
        int center = rnd.next(2, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) addEdge(edges, seen, center, i, weightFromBand(rnd.next(3)));
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < 0.12) addEdge(edges, seen, i, j, weightFromBand(rnd.next(3)));
            }
        }
    }

    relabelAndPrint(n, k, edges);
    return 0;
}
