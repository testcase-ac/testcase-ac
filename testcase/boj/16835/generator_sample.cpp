#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

static vector<pair<int, int>> allMissingEdges(int n, const set<pair<int, int>>& used) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    int s = rnd.next(1, n);
    int t = rnd.next(1, n - 1);
    if (t >= s) ++t;

    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 12);
        s = 1;
        t = n;
        for (int v = 1; v < n; ++v) addEdge(edges, v, v + 1);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        s = 1;
        t = rnd.next(2, n);
        for (int v = 1; v < n; ++v) addEdge(edges, v, v + 1);
        addEdge(edges, 1, n);
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        s = rnd.next(1, n);
        t = rnd.next(1, n - 1);
        if (t >= s) ++t;

        vector<int> vertices;
        for (int v = 1; v <= n; ++v) vertices.push_back(v);
        shuffle(vertices.begin(), vertices.end());
        for (int i = 1; i < n; ++i) {
            int parent = vertices[rnd.next(0, i - 1)];
            addEdge(edges, parent, vertices[i]);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        int leftSize = rnd.next(1, n - 1);
        s = 1;
        t = leftSize + 1;

        for (int v = 2; v <= leftSize; ++v) addEdge(edges, 1, v);
        for (int v = leftSize + 1; v <= n; ++v) addEdge(edges, 1, v);

        vector<pair<int, int>> bipartiteEdges;
        for (int a = 1; a <= leftSize; ++a) {
            for (int b = leftSize + 1; b <= n; ++b) {
                if (!edges.count({a, b})) bipartiteEdges.push_back({a, b});
            }
        }
        shuffle(bipartiteEdges.begin(), bipartiteEdges.end());
        int extra = rnd.next(0, min<int>((int)bipartiteEdges.size(), n));
        for (int i = 0; i < extra; ++i) addEdge(edges, bipartiteEdges[i].first, bipartiteEdges[i].second);
    } else {
        n = rnd.next(4, 14);
        s = rnd.next(1, n);
        t = rnd.next(1, n - 1);
        if (t >= s) ++t;

        for (int v = 2; v <= n; ++v) addEdge(edges, rnd.next(1, v - 1), v);

        vector<pair<int, int>> candidates = allMissingEdges(n, edges);
        int extra = rnd.next(0, min<int>((int)candidates.size(), n * 2));
        for (int i = 0; i < extra; ++i) addEdge(edges, candidates[i].first, candidates[i].second);
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());

    println(n, (int)output.size(), s, t);
    for (const auto& edge : output) println(edge.first, edge.second);

    return 0;
}
