#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0) ? 1 : rnd.next(2, 12);

    vector<pair<int, int>> endpoints;
    if (n == 1) {
        endpoints.emplace_back(1, 1);
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) endpoints.emplace_back(1, v);
    } else if (mode == 2) {
        for (int v = 1; v < n; ++v) endpoints.emplace_back(v, v + 1);
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parentIndex = rnd.next(0, i - 1);
            endpoints.emplace_back(order[parentIndex], order[i]);
        }
    }

    set<pair<int, int>> used;
    for (auto [a, b] : endpoints) {
        if (a > b) swap(a, b);
        used.insert({a, b});
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a; b <= n; ++b) {
            if (!used.count({a, b})) candidates.emplace_back(a, b);
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = min<int>(candidates.size(), rnd.next(0, min(12, (int)candidates.size())));
    if (mode == 3 && extraLimit < 3 && (int)candidates.size() >= 3) extraLimit = 3;
    for (int i = 0; i < extraLimit; ++i) endpoints.push_back(candidates[i]);

    int m = endpoints.size();
    vector<int> weights;
    set<int> usedWeights;
    int nextWeight = rnd.next(1, 20);
    while ((int)weights.size() < m) {
        int groupSize = rnd.next(1, 3);
        int weight = nextWeight;
        if (rnd.next(0, 5) == 0) {
            do {
                weight = rnd.next(999990, 1000000);
            } while (usedWeights.count(weight));
        }
        usedWeights.insert(weight);
        for (int i = 0; i < groupSize && (int)weights.size() < m; ++i) {
            weights.push_back(weight);
        }
        nextWeight += rnd.next(1, 7);
    }
    shuffle(weights.begin(), weights.end());

    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        auto [a, b] = endpoints[i];
        if (rnd.next(0, 1)) swap(a, b);
        edges.emplace_back(a, b, weights[i]);
    }
    shuffle(edges.begin(), edges.end());

    println(n, m);
    for (auto [a, b, w] : edges) println(a, b, w);

    return 0;
}
