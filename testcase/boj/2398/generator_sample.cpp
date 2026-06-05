#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, mode == 5 ? 10 : 14);

    vector<tuple<int, int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b, int c) {
        if (a > b) swap(a, b);
        if (a == b || used.count({a, b})) return false;
        used.insert({a, b});
        edges.emplace_back(a, b, c);
        return true;
    };

    auto cost = [&](int a, int b, int index) {
        if (mode == 1) return 1;
        if (mode == 2) return 99;
        if (mode == 3) return 1 + (abs(a - b) + index) % 7;
        if (mode == 4) return rnd.next(1, 8);
        return rnd.next(1, 99);
    };

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i + 1;
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        int parent;
        if (mode == 0) {
            parent = order[i - 1];
        } else if (mode == 1) {
            parent = order[0];
        } else {
            parent = order[rnd.next(0, i - 1)];
        }
        addEdge(parent, order[i], cost(parent, order[i], i));
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = static_cast<int>(candidates.size());
    int extra = 0;
    if (mode == 0) {
        extra = rnd.next(0, min(extraLimit, 2));
    } else if (mode == 1) {
        extra = rnd.next(0, min(extraLimit, n / 2));
    } else if (mode == 5) {
        extra = rnd.next(extraLimit / 2, extraLimit);
    } else {
        extra = rnd.next(0, min(extraLimit, n));
    }

    for (int i = 0; i < extra; ++i) {
        auto [a, b] = candidates[i];
        addEdge(a, b, cost(a, b, n + i));
    }

    shuffle(edges.begin(), edges.end());

    vector<int> terminals = order;
    shuffle(terminals.begin(), terminals.end());

    println(n, static_cast<int>(edges.size()));
    for (auto [a, b, c] : edges) println(a, b, c);
    println(terminals[0], terminals[1], terminals[2]);

    return 0;
}
