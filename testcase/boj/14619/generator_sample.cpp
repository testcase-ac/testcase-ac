#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 12);

    vector<int> h(n);
    int heightMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (heightMode == 0) {
            h[i] = rnd.next(0, 20);
        } else if (heightMode == 1) {
            h[i] = (i % 2 == 0 ? 0 : 10000);
        } else if (heightMode == 2) {
            h[i] = i * rnd.next(1, 7);
        } else {
            h[i] = 10000 - i * rnd.next(1, 7);
        }
    }
    shuffle(h.begin(), h.end());

    vector<pair<int, int>> edges;
    auto addEdge = [&](int x, int y) {
        if (x > y) swap(x, y);
        edges.push_back({x, y});
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) addEdge(center, i);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) addEdge(i, i + 1);
        for (int i = split + 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) addEdge(i, i == n ? 1 : i + 1);
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < 0.35) addEdge(i, j);
            }
        }
    }

    if (edges.empty()) addEdge(1, 2);

    vector<pair<int, int>> baseEdges = edges;
    int extra = rnd.next(0, min(8, 10000 - int(edges.size())));
    for (int i = 0; i < extra; ++i) {
        if (!baseEdges.empty() && rnd.next(0, 2) == 0) {
            edges.push_back(rnd.any(baseEdges));
        } else {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n - 1);
            if (y >= x) ++y;
            addEdge(x, y);
        }
    }
    shuffle(edges.begin(), edges.end());

    int t = rnd.next(4, 12);
    vector<pair<int, int>> queries;
    for (int i = 0; i < t; ++i) {
        int a = rnd.next(1, n);
        int k;
        if (i == 0) {
            k = 1;
        } else if (i == 1) {
            k = 2;
        } else if (i == 2) {
            k = 500;
        } else if (rnd.next(0, 3) == 0) {
            k = rnd.next(250, 500);
        } else {
            k = rnd.next(1, 20);
        }
        queries.push_back({a, k});
    }

    println(n, int(edges.size()));
    println(h);
    for (auto [x, y] : edges) println(x, y);
    println(t);
    for (auto [a, k] : queries) println(a, k);
}
