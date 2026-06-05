#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

using Edge = tuple<int, int, int>;

void addEdge(vector<Edge>& edges, int a, int b, int c) {
    edges.emplace_back(a, b, c);
}

void addRandomEdge(vector<Edge>& edges, int n, int lo = 1, int hi = 100) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) ++b;
    addEdge(edges, a, b, rnd.next(lo, hi));
}

void addInternalEdge(vector<Edge>& edges, const vector<int>& vertices, int lo, int hi) {
    if (vertices.size() < 2) return;
    int i = rnd.next(0, (int)vertices.size() - 1);
    int j = rnd.next(0, (int)vertices.size() - 2);
    if (j >= i) ++j;
    addEdge(edges, vertices[i], vertices[j], rnd.next(lo, hi));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Edge> edges;
    int n = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(2, 8);
        int last = 1;
        for (int v = 2; v <= n; ++v) {
            addEdge(edges, last, v, rnd.next(1, 20));
            last = v;
        }
        int extra = rnd.next(0, min(8, n * 2));
        while (extra--) addRandomEdge(edges, n, 1, 30);
    } else if (mode == 1) {
        n = rnd.next(4, 10);
        int leftSize = rnd.next(1, n - 2);
        vector<int> left{1}, right{n};
        for (int v = 2; v < n; ++v) {
            if ((int)left.size() <= leftSize) left.push_back(v);
            else right.push_back(v);
        }
        shuffle(left.begin(), left.end());
        shuffle(right.begin(), right.end());
        for (int i = 0; i < rnd.next(1, 4); ++i)
            addEdge(edges, rnd.any(left), rnd.any(right), rnd.next(1, 7));
        for (int i = 0; i < rnd.next(2, 8); ++i)
            addInternalEdge(edges, left, 8, 40);
        for (int i = 0; i < rnd.next(2, 8); ++i)
            addInternalEdge(edges, right, 8, 40);
    } else if (mode == 2) {
        n = rnd.next(3, 8);
        int between = rnd.next(2, n);
        int copies = rnd.next(2, 8);
        for (int i = 0; i < copies; ++i) addEdge(edges, 1, between, rnd.next(1, 25));
        if (between != n) {
            for (int v = 2; v <= n; ++v) {
                if (v != between) addEdge(edges, between, v, rnd.next(1, 25));
            }
        }
        int extra = rnd.next(0, 6);
        while (extra--) addRandomEdge(edges, n, 1, 25);
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        for (int v = 1; v <= n; ++v) {
            int to = v == n ? 1 : v + 1;
            addEdge(edges, v, to, rnd.next(1, 35));
        }
        int chords = rnd.next(1, 10);
        while (chords--) addRandomEdge(edges, n, 1, 50);
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        int middleLimit = rnd.next(1, n - 1);
        for (int v = 2; v <= middleLimit; ++v) addEdge(edges, 1, v, rnd.next(1, 20));
        for (int i = 0; i < rnd.next(0, 8); ++i) {
            int a = rnd.next(1, middleLimit);
            int b = rnd.next(1, middleLimit);
            if (a != b) addEdge(edges, a, b, rnd.next(1, 30));
        }
        if (edges.empty()) addEdge(edges, 1, 2, rnd.next(1, 20));
    } else {
        n = rnd.next(5, 12);
        vector<pair<int, int>> pairs;
        for (int a = 1; a <= n; ++a)
            for (int b = a + 1; b <= n; ++b)
                pairs.emplace_back(a, b);
        shuffle(pairs.begin(), pairs.end());
        int m = rnd.next(n - 1, min<int>(40, pairs.size()));
        for (int i = 0; i < m; ++i)
            addEdge(edges, pairs[i].first, pairs[i].second, rnd.next(1, 100));
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto [a, b, c] : edges) {
        if (rnd.next(0, 1)) swap(a, b);
        println(a, b, c);
    }

    return 0;
}
