#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());

        double density = rnd.next(0.15, 0.65);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < density) edges.push_back({order[i], order[j]});
            }
        }
    } else if (mode == 1) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());

        for (int i = 0; i + 1 < n; ++i) edges.push_back({order[i], order[i + 1]});
        for (int i = 0; i < n; ++i) {
            for (int j = i + 2; j < n; ++j) {
                if (rnd.next(0, 3) == 0) edges.push_back({order[i], order[j]});
            }
        }
    } else if (mode == 2) {
        int cycleLen = rnd.next(2, min(n, 8));
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());

        for (int i = 0; i < cycleLen; ++i) {
            edges.push_back({nodes[i], nodes[(i + 1) % cycleLen]});
        }
        for (int i = cycleLen; i < n; ++i) {
            int other = nodes[rnd.next(0, i - 1)];
            if (rnd.next(0, 1) == 0) edges.push_back({nodes[i], other});
            else edges.push_back({other, nodes[i]});
        }
    } else if (mode == 3) {
        int base = rnd.next(1, min(10, n * (n - 1)));
        for (int i = 0; i < base; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            edges.push_back({a, b});
        }

        int extra = rnd.next(base, min(70, base * 8));
        while ((int)edges.size() < extra) edges.push_back(rnd.any(edges));
    } else {
        int m = rnd.next(1, min(90, n * (n - 1)));
        while ((int)edges.size() < m) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            edges.push_back({a, b});
        }
    }

    shuffle(edges.begin(), edges.end());
    if (edges.empty()) edges.push_back({1, 2});

    println(n, (int)edges.size());
    for (const auto& edge : edges) println(edge.first, edge.second);

    return 0;
}
