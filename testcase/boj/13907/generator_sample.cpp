#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

Edge makeEdge(int a, int b, int w) {
    if (a > b) swap(a, b);
    return {a, b, w};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 14 : 10);
    int s = rnd.next(1, n);
    int d = rnd.next(1, n - 1);
    if (d >= s) ++d;

    vector<int> middle;
    for (int v = 1; v <= n; ++v) {
        if (v != s && v != d) middle.push_back(v);
    }
    shuffle(middle.begin(), middle.end());

    int pathLen = mode == 0 ? 1 : rnd.next(1, min(n - 1, 5));
    vector<int> path = {s};
    for (int i = 0; i + 1 < pathLen; ++i) path.push_back(middle[i]);
    path.push_back(d);

    vector<Edge> edges;
    set<pair<int, int>> used;

    auto addUnique = [&](int a, int b, int w) {
        if (a == b) return false;
        Edge e = makeEdge(a, b, w);
        if (!used.insert({e.a, e.b}).second) return false;
        edges.push_back(e);
        return true;
    };

    auto addParallel = [&](int a, int b, int w) {
        if (a == b) return;
        edges.push_back(makeEdge(a, b, w));
    };

    for (int i = 1; i < (int)path.size(); ++i) {
        int w = mode == 1 ? rnd.next(1, 8) : rnd.next(1, 1000);
        addUnique(path[i - 1], path[i], w);
    }

    if (mode != 0 && rnd.next(0, 1)) {
        addUnique(s, d, rnd.next(1, 1000));
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = mode == 4 ? min((int)candidates.size(), 30) : min((int)candidates.size(), 12);
    int extra = rnd.next(0, extraLimit);
    for (int i = 0; i < extra; ++i) {
        int w;
        if (mode == 2) {
            w = rnd.next(1, 20);
        } else if (mode == 3) {
            w = rnd.any(vector<int>{1, 2, 999, 1000});
        } else {
            w = rnd.next(1, 1000);
        }
        addUnique(candidates[i].first, candidates[i].second, w);
    }

    if (mode == 2 && !edges.empty()) {
        int copies = rnd.next(1, min(3, (int)edges.size()));
        for (int i = 0; i < copies; ++i) {
            Edge e = rnd.any(edges);
            addParallel(e.a, e.b, rnd.next(1, 1000));
        }
    }

    shuffle(edges.begin(), edges.end());

    int k = rnd.next(0, 8);
    println(n, (int)edges.size(), k);
    println(s, d);
    for (const Edge& e : edges) {
        println(e.a, e.b, e.w);
    }
    for (int i = 0; i < k; ++i) {
        println(rnd.next(1, 10));
    }

    return 0;
}
