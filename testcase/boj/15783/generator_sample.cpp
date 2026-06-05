#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& edges, int a, int b) {
    edges.insert({a, b});
}

static void addRandomEdge(set<pair<int, int>>& edges, int n, bool allowSelf) {
    for (int tries = 0; tries < 100; ++tries) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 1);
        if (!allowSelf && a == b) continue;
        if (edges.insert({a, b}).second) return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1)) addEdge(edges, i, i);
        }
        while (edges.empty()) addRandomEdge(edges, n, true);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        for (int i = 0; i + 1 < n; ++i) {
            if (rnd.next(0, 3) != 0) addEdge(edges, i, i + 1);
        }
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(0, n - 2);
            int b = rnd.next(a + 1, n - 1);
            addEdge(edges, a, b);
        }
        while (edges.empty()) addRandomEdge(edges, n, false);
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        int cycleSize = rnd.next(2, n);
        for (int i = 0; i < cycleSize; ++i) {
            addEdge(edges, i, (i + 1) % cycleSize);
        }
        for (int i = cycleSize; i < n; ++i) {
            if (rnd.next(0, 1)) addEdge(edges, i, rnd.next(0, cycleSize - 1));
            else addEdge(edges, rnd.next(0, cycleSize - 1), i);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        vector<int> cut = {0};
        while (cut.back() < n) {
            cut.push_back(min(n, cut.back() + rnd.next(1, 4)));
        }
        for (int c = 0; c + 1 < (int)cut.size(); ++c) {
            int l = cut[c], r = cut[c + 1];
            if (r - l == 1) {
                if (rnd.next(0, 4) == 0) addEdge(edges, l, l);
            } else {
                for (int v = l; v < r; ++v) addEdge(edges, v, v + 1 == r ? l : v + 1);
            }
            if (c + 2 < (int)cut.size() && rnd.next(0, 2) != 0) {
                addEdge(edges, rnd.next(l, r - 1), rnd.next(cut[c + 1], cut[c + 2] - 1));
            }
        }
        while (edges.empty()) addRandomEdge(edges, n, true);
    } else {
        n = rnd.next(2, 18);
        int target = rnd.next(1, min(45, n * n));
        bool allowSelf = rnd.next(0, 3) == 0;
        while ((int)edges.size() < target) addRandomEdge(edges, n, allowSelf);
    }

    vector<int> perm(n);
    for (int i = 0; i < n; ++i) perm[i] = i;
    shuffle(perm.begin(), perm.end());

    vector<pair<int, int>> out;
    for (auto [a, b] : edges) out.push_back({perm[a], perm[b]});
    shuffle(out.begin(), out.end());

    println(n, (int)out.size());
    for (auto [a, b] : out) println(a, b);

    return 0;
}
