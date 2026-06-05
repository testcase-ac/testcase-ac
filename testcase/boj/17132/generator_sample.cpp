#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int pickWeight(int pattern, int index, int n) {
    if (pattern == 0) {
        return rnd.next(1, 200);
    }
    if (pattern == 1) {
        return 1;
    }
    if (pattern == 2) {
        return 200;
    }
    if (pattern == 3) {
        return 1 + (index % 200);
    }
    if (pattern == 4) {
        return 200 - (index % 200);
    }
    return rnd.any(vector<int>{1, 2, 3, 50, 100, 199, 200});
}

void addEdge(vector<tuple<int, int, int>>& edges, int u, int v, int w) {
    if (rnd.next(2) == 0) {
        swap(u, v);
    }
    edges.emplace_back(u, v, w);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 18);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
    } else if (mode == 3) {
        n = rnd.next(2, 31);
    } else if (mode == 4) {
        n = rnd.next(2, 24);
    } else {
        n = rnd.next(3, 24);
    }

    int weightPattern = rnd.next(6);
    vector<tuple<int, int, int>> edges;

    if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, pickWeight(weightPattern, i - 1, n));
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                addEdge(edges, center, v, pickWeight(weightPattern, (int)edges.size(), n));
            }
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, v / 2, v, pickWeight(weightPattern, v - 2, n));
        }
    } else if (mode == 4) {
        for (int v = 2; v <= n; ++v) {
            int parent = rnd.next(1, v - 1);
            addEdge(edges, parent, v, pickWeight(weightPattern, v - 2, n));
        }
    } else if (mode == 5) {
        int pathLen = rnd.next(2, n - 1);
        for (int i = 1; i < pathLen; ++i) {
            addEdge(edges, i, i + 1, pickWeight(weightPattern, i - 1, n));
        }
        for (int v = pathLen + 1; v <= n; ++v) {
            int attach = rnd.next(1, pathLen);
            addEdge(edges, attach, v, pickWeight(weightPattern, (int)edges.size(), n));
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [u, v, w] : edges) {
        println(u, v, w);
    }

    return 0;
}
