#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b) {
        if (a == b) return;
        if (a > b) swap(a, b);
        if (used.insert({a, b}).second) edges.push_back({a, b});
    };

    if (mode == 0) {
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                candidates.push_back({i, j});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int q = rnd.next(1, (int)candidates.size());
        for (int i = 0; i < q; ++i) addEdge(candidates[i].first, candidates[i].second);
    } else if (mode == 1) {
        n = max(n, 3);
        addEdge(1, 2);
        addEdge(2, 3);
        addEdge(1, 3);
        for (int v = 4; v <= n; ++v) {
            addEdge(rnd.next(1, v - 1), v);
            if (rnd.next(0, 1)) addEdge(rnd.next(1, v - 1), v);
        }
    } else if (mode == 2) {
        n = max(n, 5);
        int left = rnd.next(2, n - 2);
        vector<int> a, b;
        for (int i = 1; i <= left; ++i) a.push_back(i);
        for (int i = left + 1; i <= n; ++i) b.push_back(i);
        for (int x : a) {
            for (int y : b) {
                if (rnd.next(0, 99) < 45) addEdge(x, y);
            }
        }
        if (edges.empty()) addEdge(a[0], b[0]);
        if (left >= 2 && rnd.next(0, 1)) addEdge(a[0], a[1]);
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) addEdge(v - 1, v);
        if (n >= 4 && rnd.next(0, 1)) addEdge(1, 3);
        if (n >= 5 && rnd.next(0, 1)) addEdge(2, 5);
        for (int i = 0; i < n / 2; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else {
        n = max(n, 6);
        int split = rnd.next(3, n - 2);
        addEdge(1, 2);
        addEdge(2, 3);
        if (rnd.next(0, 1)) addEdge(1, 3);
        for (int v = 4; v <= split; ++v) addEdge(rnd.next(1, v - 1), v);
        for (int v = split + 2; v <= n; ++v) addEdge(split + 1, v);
        if (rnd.next(0, 1)) addEdge(split, split + 1);
    }

    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) perm[i] = i;
    shuffle(perm.begin() + 1, perm.end());
    for (auto& edge : edges) {
        edge = {perm[edge.first], perm[edge.second]};
        if (edge.first > edge.second) swap(edge.first, edge.second);
    }

    println(n, (int)edges.size());
    for (auto [a, b] : edges) println(a, b);

    return 0;
}
