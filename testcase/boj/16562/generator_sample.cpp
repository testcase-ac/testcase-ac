#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = findRoot(parent, parent[x]);
}

void unite(vector<int>& parent, int a, int b) {
    a = findRoot(parent, a);
    b = findRoot(parent, b);
    if (a != b) parent[b] = a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? 1 : rnd.next(2, 14);
    vector<int> cost(n + 1);

    int lo = rnd.next(1, 30);
    int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 120)));
    for (int i = 1; i <= n; ++i) cost[i] = rnd.next(lo, hi);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges.clear();
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) edges.push_back({i, i + 1});
    } else if (mode == 2) {
        int groups = rnd.next(2, min(n, 5));
        vector<int> label(n + 1);
        for (int i = 1; i <= n; ++i) label[i] = rnd.next(0, groups - 1);
        for (int g = 0; g < groups; ++g) {
            vector<int> members;
            for (int i = 1; i <= n; ++i)
                if (label[i] == g) members.push_back(i);
            shuffle(members.begin(), members.end());
            for (int i = 1; i < (int)members.size(); ++i) {
                edges.push_back({members[i - 1], members[i]});
            }
        }
    } else if (mode == 3) {
        double density = rnd.next(0.25, 0.75);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) edges.push_back({i, j});
            }
        }
    } else {
        int baseEdges = rnd.next(0, min(20, n * 2));
        for (int i = 0; i < baseEdges; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            edges.push_back({a, b});
        }
    }

    int noisyEdges = rnd.next(0, min(10, n));
    for (int i = 0; i < noisyEdges; ++i) {
        if (!edges.empty() && rnd.next(0, 2) == 0) {
            edges.push_back(rnd.any(edges));
        } else {
            int a = rnd.next(1, n);
            int b = rnd.next(0, 3) == 0 ? a : rnd.next(1, n);
            edges.push_back({a, b});
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    for (auto [a, b] : edges) unite(parent, a, b);

    vector<int> minCost(n + 1, 10001);
    for (int i = 1; i <= n; ++i) {
        int root = findRoot(parent, i);
        minCost[root] = min(minCost[root], cost[i]);
    }

    int required = 0;
    for (int i = 1; i <= n; ++i)
        if (minCost[i] != 10001) required += minCost[i];

    int k;
    int budgetMode = rnd.next(0, 2);
    if (budgetMode == 0) {
        k = required;
    } else if (budgetMode == 1) {
        k = rnd.next(1, required);
    } else {
        k = rnd.next(required, min(10000000, required + rnd.next(0, 200)));
    }

    println(n, (int)edges.size(), k);
    println(vector<int>(cost.begin() + 1, cost.end()));
    for (auto [a, b] : edges) println(a, b);

    return 0;
}
