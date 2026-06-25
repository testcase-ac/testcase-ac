#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

long long randomValue() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(1, 9);
    if (mode == 2) return rnd.next(10, 1000);
    return rnd.next(100000000, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 18);
    vector<vector<long long>> a(n, vector<long long>(n, 0));
    set<pair<int, int>> used;

    auto addEdge = [&](int u, int v) {
        if ((int)used.size() >= 5 * n) return;
        if (used.insert({u, v}).second) {
            a[u][v] = randomValue();
        }
    };

    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i;
    shuffle(p.begin(), p.end());

    if (mode == 0) {
        int edgeCount = rnd.next(0, min(5 * n, n * n));
        vector<pair<int, int>> candidates;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                candidates.push_back({i, j});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < edgeCount; ++i) addEdge(candidates[i].first, candidates[i].second);
    } else if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) addEdge(p[i], p[i + 1]);
        if (rnd.next(0, 1)) addEdge(p.back(), p.front());
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) addEdge(p[i], p[(i + 1) % n]);
        int extra = rnd.next(0, min(4 * n, n * n - n));
        while (extra--) addEdge(rnd.next(0, n - 1), rnd.next(0, n - 1));
    } else if (mode == 3) {
        int center = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i == center) continue;
            addEdge(center, i);
            if (rnd.next(0, 1)) addEdge(i, center);
        }
        int loops = rnd.next(0, n);
        while (loops--) addEdge(rnd.next(0, n - 1), rnd.next(0, n - 1));
    } else if (mode == 4) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i + 1 < split; ++i) addEdge(p[i], p[i + 1]);
        for (int i = split; i + 1 < n; ++i) addEdge(p[i + 1], p[i]);
        int extra = rnd.next(0, 2 * n);
        while (extra--) {
            int side = rnd.next(0, 1);
            if (side == 0) {
                int x = rnd.next(0, split - 1);
                int y = rnd.next(0, split - 1);
                addEdge(p[x], p[y]);
            } else {
                int x = rnd.next(split, n - 1);
                int y = rnd.next(split, n - 1);
                addEdge(p[x], p[y]);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) != 0) addEdge(i, i);
        }
        int edgeCount = rnd.next(n / 2, 5 * n);
        while ((int)used.size() < edgeCount) {
            int u = rnd.next(0, n - 1);
            int v = rnd.next(0, n - 1);
            addEdge(u, v);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
