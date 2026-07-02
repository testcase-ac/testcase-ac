#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a == b) return;
    edges.insert(minmax(a, b));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 0;
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(0, 2);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
        if (n >= 4 && rnd.next(0, 1)) addEdge(edges, 1, n);
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) addEdge(edges, center, v);
    } else if (mode == 4) {
        n = rnd.next(3, 11);
        int cliqueSize = rnd.next(2, n);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < cliqueSize; ++i)
            for (int j = i + 1; j < cliqueSize; ++j)
                addEdge(edges, vertices[i], vertices[j]);
    } else if (mode == 5) {
        n = rnd.next(4, 14);
        vector<int> color(n + 1);
        int groups = rnd.next(2, min(4, n));
        for (int v = 1; v <= n; ++v) color[v] = rnd.next(0, groups - 1);
        for (int a = 1; a <= n; ++a)
            for (int b = a + 1; b <= n; ++b)
                if (color[a] != color[b] && rnd.next(0, 99) < 65)
                    addEdge(edges, a, b);
    } else if (mode == 6) {
        n = rnd.next(5, 18);
        int maxEdges = n * (n - 1) / 2;
        int target = rnd.next(0, min(maxEdges, 40));
        while (static_cast<int>(edges.size()) < target) {
            addEdge(edges, rnd.next(1, n), rnd.next(1, n));
        }
    } else {
        n = rnd.next(6, 20);
        int pathLen = rnd.next(2, n);
        for (int i = 1; i < pathLen; ++i) addEdge(edges, i, i + 1);
        int extra = rnd.next(0, min(25, n * (n - 1) / 2));
        while (static_cast<int>(edges.size()) < extra) {
            addEdge(edges, rnd.next(1, n), rnd.next(1, n));
        }
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());

    println(n, static_cast<int>(output.size()));
    for (auto [a, b] : output) {
        if (rnd.next(0, 1)) swap(a, b);
        println(a, b);
    }

    return 0;
}
