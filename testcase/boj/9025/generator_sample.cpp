#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    int b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(2, mode == 4 ? 12 : 9);

        vector<Edge> edges;
        set<pair<int, int>> used;

        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());

        auto addEdge = [&](int a, int b, int w) {
            if (a > b) {
                swap(a, b);
            }
            if (a == b || !used.insert({a, b}).second) {
                return false;
            }
            edges.push_back({a, b, w});
            return true;
        };

        int low = rnd.next(1, 20);
        int high = rnd.next(low, min(100000, low + rnd.next(0, 200)));

        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            int child = order[i];
            int weight;
            if (mode == 0) {
                weight = low + i - 1;
            } else if (mode == 1) {
                weight = max(1, high - i + 1);
            } else if (mode == 2) {
                weight = rnd.any(vector<int>{1, low, high, 100000});
            } else {
                weight = rnd.next(low, high);
            }
            addEdge(parent, child, weight);
        }

        int maxExtra = min(n * (n - 1) / 2 - (n - 1), mode == 4 ? 20 : 8);
        int extra = rnd.next(0, maxExtra);
        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (!used.count({u, v})) {
                    candidates.push_back({u, v});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());

        for (int i = 0; i < extra && i < static_cast<int>(candidates.size()); ++i) {
            int weight;
            if (mode == 3) {
                weight = rnd.next(99980, 100000);
            } else if (mode == 4) {
                weight = rnd.wnext(100000, 3) + 1;
            } else {
                weight = rnd.next(1, 100000);
            }
            addEdge(candidates[i].first, candidates[i].second, weight);
        }

        shuffle(edges.begin(), edges.end());

        int s = rnd.next(1, n);
        int t = rnd.next(1, n - 1);
        if (t >= s) {
            ++t;
        }

        println(n, static_cast<int>(edges.size()), s, t);
        for (const Edge& edge : edges) {
            println(edge.u, edge.v, edge.b);
        }
    }

    return 0;
}
