#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

static void addEdge(vector<Edge>& edges, set<pair<int, int>>& seen, int a, int b, int w) {
    if (a > b) swap(a, b);
    if (a == b || !seen.insert({a, b}).second) return;
    edges.emplace_back(a, b, w);
}

static vector<pair<int, int>> allPairs(int n) {
    vector<pair<int, int>> pairs;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            pairs.emplace_back(i, j);
        }
    }
    shuffle(pairs.begin(), pairs.end());
    return pairs;
}

static void randomizePresentation(vector<Edge>& edges) {
    vector<int> label((int)edges.size() + 101);
    int n = 0;
    for (auto [a, b, w] : edges) n = max(n, max(a, b));
    label.resize(n + 1);
    for (int i = 1; i <= n; ++i) label[i] = i;
    shuffle(label.begin() + 1, label.end());

    for (auto& [a, b, w] : edges) {
        a = label[a];
        b = label[b];
        if (rnd.next(2)) swap(a, b);
    }
    shuffle(edges.begin(), edges.end());
}

static vector<Edge> makeDisconnected(int n) {
    vector<Edge> edges;
    set<pair<int, int>> seen;

    int split = rnd.next(1, n - 1);
    vector<pair<int, int>> candidates;
    for (int i = 1; i <= split; ++i) {
        for (int j = i + 1; j <= split; ++j) candidates.emplace_back(i, j);
    }
    for (int i = split + 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) candidates.emplace_back(i, j);
    }
    shuffle(candidates.begin(), candidates.end());

    int target = candidates.empty() ? 0 : rnd.next(0, min((int)candidates.size(), 18));
    for (int i = 0; i < target; ++i) {
        addEdge(edges, seen, candidates[i].first, candidates[i].second, rnd.next(1, 10000));
    }
    return edges;
}

static vector<Edge> makeTreeLike(int n) {
    vector<Edge> edges;
    set<pair<int, int>> seen;

    int base = rnd.next(1, 9000);
    int spread = rnd.next(0, 40);
    for (int v = 2; v <= n; ++v) {
        int parent = rnd.next(1, v - 1);
        addEdge(edges, seen, v, parent, min(10000, base + rnd.next(0, spread)));
    }

    int extra = rnd.next(0, min(12, n * (n - 1) / 2 - (n - 1)));
    for (auto [a, b] : allPairs(n)) {
        if ((int)edges.size() >= n - 1 + extra) break;
        addEdge(edges, seen, a, b, rnd.next(1, 10000));
    }
    return edges;
}

static vector<Edge> makeDenseSmall(int n) {
    vector<Edge> edges;
    set<pair<int, int>> seen;

    int cap = min(n * (n - 1) / 2, rnd.next(max(n - 1, 1), min(35, n * (n - 1) / 2)));
    int anchor = rnd.next(1, 9800);
    int mode = rnd.next(3);
    for (auto [a, b] : allPairs(n)) {
        int w;
        if (mode == 0) {
            w = rnd.next(1, 10000);
        } else if (mode == 1) {
            w = min(10000, anchor + rnd.next(0, 200));
        } else {
            w = rnd.any(vector<int>{1, 2, 3, 9998, 9999, 10000});
        }
        addEdge(edges, seen, a, b, w);
        if ((int)edges.size() == cap) break;
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(4, 8);
    for (int tc = 0; tc < datasets; ++tc) {
        int n = rnd.next(2, 12);
        int mode = rnd.next(3);

        vector<Edge> edges;
        if (mode == 0) {
            edges = makeDisconnected(n);
        } else if (mode == 1) {
            edges = makeTreeLike(n);
        } else {
            edges = makeDenseSmall(n);
        }

        randomizePresentation(edges);
        println(n, (int)edges.size());
        for (auto [a, b, w] : edges) {
            println(a, b, w);
        }
    }

    println(0, 0);
    return 0;
}
