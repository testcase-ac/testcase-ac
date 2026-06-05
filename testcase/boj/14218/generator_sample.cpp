#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

Edge randomEdge(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) ++b;
    if (rnd.next(2)) swap(a, b);
    return {a, b};
}

void maybeOrient(Edge& edge) {
    if (rnd.next(2)) swap(edge.first, edge.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    vector<Edge> initial;

    if (mode == 0) {
        int componentSize = rnd.next(1, n);
        for (int v = 2; v <= componentSize; ++v) {
            initial.emplace_back(rnd.next(1, v - 1), v);
        }
        int extras = rnd.next(0, max(0, componentSize - 1));
        while (extras--) initial.push_back(randomEdge(max(2, componentSize)));
        if (initial.empty()) initial.push_back(randomEdge(n));
    } else if (mode == 1) {
        for (int v = 1; v < n; ++v) initial.emplace_back(v, v + 1);
        int keep = rnd.next(1, n - 1);
        shuffle(initial.begin(), initial.end());
        initial.resize(keep);
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center && rnd.next(3) != 0) initial.emplace_back(center, v);
        }
        if (initial.empty()) initial.push_back(randomEdge(n));
    } else if (mode == 3) {
        vector<Edge> candidates;
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                candidates.emplace_back(i, j);
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(1, min<int>(candidates.size(), rnd.next(n, 2 * n)));
        initial.assign(candidates.begin(), candidates.begin() + m);
    } else {
        Edge repeated = randomEdge(n);
        int m = rnd.next(1, 2 * n);
        for (int k = 0; k < m; ++k) {
            if (rnd.next(3) == 0) initial.push_back(randomEdge(n));
            else initial.push_back(repeated);
        }
    }

    shuffle(initial.begin(), initial.end());
    for (Edge& edge : initial) maybeOrient(edge);

    int q = rnd.next(1, 20);
    vector<Edge> plans;
    vector<Edge> allPairs;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            allPairs.emplace_back(i, j);
    shuffle(allPairs.begin(), allPairs.end());

    for (int k = 0; k < q; ++k) {
        Edge edge;
        if (k < (int)allPairs.size() && rnd.next(4) != 0) {
            edge = allPairs[k];
        } else if (!initial.empty() && rnd.next(3) == 0) {
            edge = initial[rnd.next((int)initial.size())];
        } else {
            edge = randomEdge(n);
        }
        maybeOrient(edge);
        plans.push_back(edge);
    }

    println(n, (int)initial.size());
    for (const Edge& edge : initial) println(edge.first, edge.second);
    println(q);
    for (const Edge& edge : plans) println(edge.first, edge.second);

    return 0;
}
