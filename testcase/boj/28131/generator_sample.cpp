#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int randWeight(int k, int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, k) * rnd.next(1, 4);
    if (mode == 2) return rnd.next(900, 1000);
    return rnd.next(1, 1000);
}

void addEdge(vector<Edge>& edges, int u, int v, int w) {
    if (u != v) edges.push_back({u, v, w});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 4 ? rnd.next(12, 30) : rnd.next(2, 10));
    int k = rnd.next(1, 50);
    int s = rnd.next(1, n);
    int t = rnd.next(1, n - 1);
    if (t >= s) ++t;

    vector<Edge> edges;
    int weightMode = rnd.next(0, 3);

    if (mode == 0) {
        int cur = s;
        vector<int> middle;
        for (int v = 1; v <= n; ++v) {
            if (v != s && v != t && rnd.next(0, 1)) middle.push_back(v);
        }
        shuffle(middle.begin(), middle.end());
        int take = middle.empty() ? 0 : rnd.next(0, min<int>(3, middle.size()));
        for (int i = 0; i < take; ++i) {
            addEdge(edges, cur, middle[i], randWeight(k, weightMode));
            cur = middle[i];
        }
        int prefix = 0;
        for (const Edge& e : edges) prefix += e.w;
        int finalWeight = rnd.next(1, 20);
        if (k > 1 && rnd.next(0, 1)) {
            int need = (k - prefix % k) % k;
            finalWeight = need == 0 ? k : need;
        }
        addEdge(edges, cur, t, finalWeight);
    } else if (mode == 1) {
        addEdge(edges, s, t, rnd.next(1, 1000));
        addEdge(edges, t, s, rnd.next(1, 1000));
        int pivot = rnd.next(1, n);
        if (pivot == s) pivot = t;
        addEdge(edges, s, pivot, randWeight(k, weightMode));
        addEdge(edges, pivot, s, randWeight(k, weightMode));
        addEdge(edges, pivot, t, randWeight(k, weightMode));
    } else if (mode == 2) {
        for (int v = 1; v <= n; ++v) {
            if (v != t && rnd.next(0, 1)) {
                int to = rnd.next(1, n - 1);
                if (to >= v) ++to;
                addEdge(edges, v, to, randWeight(k, weightMode));
            }
        }
        if (edges.empty()) addEdge(edges, t, s, randWeight(k, weightMode));
    } else if (mode == 3) {
        int base = rnd.next(1, n);
        int other = rnd.next(1, n - 1);
        if (other >= base) ++other;
        int copies = rnd.next(2, 6);
        for (int i = 0; i < copies; ++i) {
            addEdge(edges, base, other, randWeight(k, weightMode));
        }
        addEdge(edges, s, base, randWeight(k, weightMode));
        addEdge(edges, other, t, randWeight(k, weightMode));
    } else {
        for (int i = 1; i < n; ++i) {
            addEdge(edges, i, i + 1, randWeight(k, weightMode));
            if (rnd.next(0, 2) == 0) addEdge(edges, i + 1, i, randWeight(k, weightMode));
        }
        addEdge(edges, s, t, randWeight(k, weightMode));
    }

    int maxM = n * (n - 1);
    shuffle(edges.begin(), edges.end());
    if ((int)edges.size() > maxM) edges.resize(maxM);

    vector<pair<int, int>> pairs;
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (u != v) pairs.push_back({u, v});
        }
    }
    shuffle(pairs.begin(), pairs.end());

    int targetM = rnd.next(max<int>(1, edges.size()), min(100, maxM));
    for (const auto& [u, v] : pairs) {
        if ((int)edges.size() >= targetM) break;
        addEdge(edges, u, v, randWeight(k, weightMode));
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), k);
    println(s, t);
    for (const Edge& e : edges) println(e.u, e.v, e.w);

    return 0;
}
