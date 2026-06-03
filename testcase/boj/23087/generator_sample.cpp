#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

using Edge = tuple<int, int, int>;

void addEdge(vector<Edge>& edges, int u, int v, int w) {
    edges.emplace_back(u, v, w);
}

void addRandomNoise(vector<Edge>& edges, int n, int limit) {
    while ((int)edges.size() < limit) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) ++v;
        int w = rnd.next(1, 30);
        if (rnd.next(8) == 0) w = 200000;
        addEdge(edges, u, v, w);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    int x = 1;
    int y = 2;
    vector<Edge> edges;

    if (mode == 0) {
        n = rnd.next(3, 9);
        x = 1;
        y = n;
        int left = rnd.next(1, n - 2);
        for (int i = 1; i < left; ++i) addEdge(edges, i, i + 1, rnd.next(1, 20));
        addEdge(edges, n, rnd.next(1, n - 1), rnd.next(1, 20));
        addRandomNoise(edges, n - 1, rnd.next(2, min(12, (n - 1) * (n - 2))));
    } else if (mode == 1) {
        n = rnd.next(3, 7);
        x = 1;
        y = n;
        int copiesA = rnd.next(2, 5);
        int copiesB = rnd.next(1, 4);
        for (int i = 0; i < copiesA; ++i) addEdge(edges, x, 2, 1);
        for (int i = 0; i < copiesB; ++i) addEdge(edges, 2, y, 2);
        addEdge(edges, x, y, rnd.next(5, 12));
        addRandomNoise(edges, n, rnd.next((int)edges.size(), 14));
    } else if (mode == 2) {
        n = rnd.next(5, 8);
        x = 1;
        y = n;
        int total = rnd.next(6, 18);
        addEdge(edges, x, 2, total / 2);
        addEdge(edges, 2, 3, total - total / 2);
        addEdge(edges, 3, y, 1);
        addEdge(edges, x, y, total + 1);
        addEdge(edges, x, 4, total);
        addEdge(edges, 4, y, 1);
        addRandomNoise(edges, n, rnd.next(7, 15));
    } else if (mode == 3) {
        n = rnd.next(4, 9);
        x = rnd.next(1, n);
        y = rnd.next(1, n - 1);
        if (y >= x) ++y;
        for (int i = 1; i <= n; ++i) {
            int v = i == n ? 1 : i + 1;
            addEdge(edges, i, v, rnd.next(1, 9));
        }
        addEdge(edges, x, y, rnd.next(1, 4));
        addEdge(edges, x, y, rnd.next(1, 4));
        addRandomNoise(edges, n, rnd.next(n + 2, 20));
    } else if (mode == 4) {
        n = rnd.next(5, 10);
        x = 1;
        y = n;
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1, rnd.next(1, 5));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (i != j && rnd.next(100) < 28) addEdge(edges, i, j, rnd.next(1, 40));
    } else {
        n = 2;
        x = 1;
        y = 2;
        addEdge(edges, 1, 2, 1);
        addEdge(edges, 2, 1, 200000);
    }

    while ((int)edges.size() < 2) addRandomNoise(edges, n, 2);
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), x, y);
    for (auto [u, v, w] : edges) println(u, v, w);

    return 0;
}
