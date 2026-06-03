#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a == b) return;
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = rnd.next(1, 18);
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        for (int i = 1; i <= n; ++i) addEdge(edges, i, i == n ? 1 : i + 1);
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        for (int i = 2; i <= n; ++i) addEdge(edges, 1, i);
        for (int i = 2; i <= n; ++i) {
            if (rnd.next(4) == 0) addEdge(edges, i, rnd.next(2, n));
        }
    } else if (mode == 4) {
        n = rnd.next(4, 18);
        int left = rnd.next(1, n - 1);
        for (int i = 1; i <= left; ++i) {
            for (int j = left + 1; j <= n; ++j) {
                if (rnd.next(100) < rnd.next(25, 80)) addEdge(edges, i, j);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(4, 18);
        int probability = rnd.next(25, 75);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(100) < probability) addEdge(edges, i, j);
            }
        }
    } else {
        n = rnd.next(2, 18);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) addEdge(edges, i, j);
        }
        int keep = rnd.next(n - 1, min<int>(edges.size(), n * 4));
        vector<pair<int, int>> dense(edges.begin(), edges.end());
        shuffle(dense.begin(), dense.end());
        edges.clear();
        for (int i = 0; i < keep; ++i) edges.insert(dense[i]);
    }

    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());

    vector<pair<int, int>> output;
    for (auto [a, b] : edges) output.push_back({perm[a], perm[b]});
    shuffle(output.begin(), output.end());

    long long d;
    int dMode = rnd.next(5);
    if (dMode == 0) {
        d = rnd.next(1, 8);
    } else if (dMode == 1) {
        d = rnd.next(9, 100);
    } else if (dMode == 2) {
        d = rnd.next(101, 100000);
    } else if (dMode == 3) {
        d = 1000000000LL - rnd.next(0, 1000);
    } else {
        d = 1LL << rnd.next(1, 29);
    }

    println(n, int(output.size()));
    for (auto [a, b] : output) println(a, b);
    println(d);

    return 0;
}
