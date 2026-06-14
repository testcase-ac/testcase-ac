#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

static void addEdge(vector<Edge>& edges, int u, int v, int w) {
    if (u == v) return;
    edges.emplace_back(u, v, w);
}

static vector<int> randomWater(int n) {
    vector<int> water(n + 1);
    int mode = rnd.next(3);
    for (int i = 1; i <= n; ++i) {
        if (mode == 0) {
            water[i] = rnd.next(1, 9);
        } else if (mode == 1) {
            water[i] = rnd.next(999990, 1000000);
        } else {
            water[i] = (rnd.next(5) == 0 ? rnd.next(100000, 1000000) : rnd.next(1, 30));
        }
    }
    return water;
}

static void shuffleLabels(vector<Edge>& edges, int& s, int& t, vector<int>& water) {
    int n = (int)water.size() - 1;
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());

    vector<int> newWater(n + 1);
    for (int i = 1; i <= n; ++i) newWater[perm[i]] = water[i];
    for (auto& [u, v, w] : edges) {
        u = perm[u];
        v = perm[v];
        if (rnd.next(2)) swap(u, v);
    }
    s = perm[s];
    t = perm[t];
    water = newWater;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    vector<int> water = randomWater(n);
    vector<Edge> edges;
    int s = 1;
    int t = n;

    if (mode == 0) {
        n = rnd.next(3, 10);
        water = randomWater(n);
        s = 1;
        t = n;
        int componentSize = rnd.next(1, n - 1);
        for (int i = 1; i < componentSize; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 20));
        }
        if (componentSize + 1 < n) {
            for (int i = componentSize + 1; i < n; ++i) {
                addEdge(edges, i, i + 1, rnd.next(1, 20));
            }
        }
        if (edges.empty()) {
            addEdge(edges, 2, 3, rnd.next(1, 20));
        }
    } else if (mode == 1) {
        n = rnd.next(4, 9);
        water = randomWater(n);
        s = 1;
        t = n;
        int a = 2;
        int b = 3;
        int dist = rnd.next(2, 20);
        int leftA = rnd.next(1, dist - 1);
        int leftB = rnd.next(1, dist - 1);
        addEdge(edges, s, a, leftA);
        addEdge(edges, a, t, dist - leftA);
        addEdge(edges, s, b, leftB);
        addEdge(edges, b, t, dist - leftB);
        for (int v = 4; v < n; ++v) {
            addEdge(edges, v, rnd.next(1, v - 1), rnd.next(dist + 1, dist + 20));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        water = randomWater(n);
        s = 1;
        t = n;
        addEdge(edges, 1, 2, rnd.next(1, 5));
        addEdge(edges, 1, 2, rnd.next(1, 5));
        for (int i = 2; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 8));
            if (rnd.next(2)) addEdge(edges, i, i + 1, rnd.next(1, 8));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 14);
        water = randomWater(n);
        s = 1;
        t = n;
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, rnd.next(1, 15));
        }
        int extra = rnd.next(1, min(18, n * (n - 1) / 2));
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(edges, u, v, rnd.next(1, 25));
        }
    } else {
        n = rnd.next(2, 8);
        water = randomWater(n);
        s = rnd.next(1, n);
        t = rnd.next(1, n - 1);
        if (t >= s) ++t;
        addEdge(edges, s, t, rnd.next(1, 1000000));
        int extra = rnd.next(0, 12);
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            addEdge(edges, u, v, rnd.next(1, 1000000));
        }
    }

    shuffleLabels(edges, s, t, water);
    shuffle(edges.begin(), edges.end());

    println(n);
    vector<int> outputWater(water.begin() + 1, water.end());
    println(outputWater);
    println((int)edges.size());
    for (auto [u, v, w] : edges) {
        println(u, v, w);
    }
    println(s, t);

    return 0;
}
