#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int s = rnd.next(1, n);
    int e = rnd.next(1, n - 1);
    if (e >= s) ++e;

    set<pair<int, int>> used;
    vector<pair<int, int>> edges;

    auto addEdge = [&](int u, int v) {
        if (u == v) return false;
        pair<int, int> edge = minmax(u, v);
        if (!used.insert(edge).second) return false;
        edges.push_back(edge);
        return true;
    };

    auto addRandomEdges = [&](int target) {
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (!used.count({u, v})) candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (auto [u, v] : candidates) {
            if ((int)edges.size() >= target) break;
            addEdge(u, v);
        }
    };

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        addEdge(s, e);
        addRandomEdges(rnd.next(1, min(n * (n - 1) / 2, n + 4)));
    } else if (mode == 1) {
        vector<int> middle;
        for (int v = 1; v <= n; ++v) {
            if (v != s && v != e) middle.push_back(v);
        }
        shuffle(middle.begin(), middle.end());
        int take = rnd.next(0, min((int)middle.size(), 5));
        int prev = s;
        for (int i = 0; i < take; ++i) {
            addEdge(prev, middle[i]);
            prev = middle[i];
        }
        addEdge(prev, e);
        addRandomEdges(rnd.next((int)edges.size(), min(n * (n - 1) / 2, n + 6)));
    } else if (mode == 2) {
        vector<int> left = {s};
        vector<int> right = {e};
        for (int v = 1; v <= n; ++v) {
            if (v == s || v == e) continue;
            (rnd.next(0, 1) == 0 ? left : right).push_back(v);
        }
        if (left.size() >= 2) {
            for (int i = 1; i < (int)left.size(); ++i) addEdge(left[i - 1], left[i]);
        }
        if (right.size() >= 2) {
            for (int i = 1; i < (int)right.size(); ++i) addEdge(right[i - 1], right[i]);
        }
        if (edges.empty()) addEdge(s, right.back());
        int extra = rnd.next(0, 4);
        for (int i = 0; i < extra; ++i) {
            const vector<int>& side = rnd.next(0, 1) == 0 ? left : right;
            if (side.size() >= 2) addEdge(rnd.any(side), rnd.any(side));
        }
    } else {
        for (int v = 1; v <= n; ++v) {
            if (v != s && rnd.next(0, 2) == 0) addEdge(s, v);
        }
        for (int v = 1; v <= n; ++v) {
            if (v != e && rnd.next(0, 2) == 0) addEdge(v, e);
        }
        addRandomEdges(rnd.next(max(1, (int)edges.size()), min(n * (n - 1) / 2, n + 5)));
    }

    if (edges.empty()) addEdge(s, e);
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), s, e);
    for (auto [u, v] : edges) println(u, v);

    return 0;
}
