#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int randomWeight(int mode) {
    if (mode == 0) return rnd.next(-25, 25);
    if (mode == 1) return rnd.next(-1000, 1000);
    if (mode == 2) return rnd.next(-1000, -1);
    if (mode == 3) return rnd.next(0, 1000);
    return rnd.next(-200, 200);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = (mode == 0 ? 1 : rnd.next(2, 12));

        vector<pair<int, int>> edges;
        set<pair<int, int>> used;

        auto addEdge = [&](int a, int b) {
            if (a != b && used.insert({a, b}).second) {
                edges.push_back({a, b});
            }
        };

        if (n > 1) {
            vector<int> order;
            for (int i = 1; i < n; ++i) order.push_back(i);
            shuffle(order.begin(), order.end());

            int prev = 0;
            for (int v : order) {
                addEdge(prev, v);
                prev = v;
            }

            if (mode == 1) {
                addEdge(order.back(), 0);
            } else if (mode == 2) {
                int v = rnd.any(order);
                addEdge(0, v);
                addEdge(v, 0);
            } else if (mode == 3 && n >= 3) {
                addEdge(order[0], order[1]);
                addEdge(order[1], 0);
            } else if (mode == 4) {
                for (int v : order) addEdge(0, v);
            }

            vector<pair<int, int>> candidates;
            for (int a = 0; a < n; ++a) {
                for (int b = 0; b < n; ++b) {
                    if (a != b && !used.count({a, b})) candidates.push_back({a, b});
                }
            }
            shuffle(candidates.begin(), candidates.end());

            int extraLimit = min<int>(candidates.size(), rnd.next(0, min(24, (int)candidates.size())));
            for (int i = 0; i < extraLimit; ++i) addEdge(candidates[i].first, candidates[i].second);
        }

        int weightMode = rnd.next(0, 4);
        println(n, (int)edges.size());
        for (auto [a, b] : edges) {
            println(a, b, randomWeight(weightMode));
        }
    }

    return 0;
}
