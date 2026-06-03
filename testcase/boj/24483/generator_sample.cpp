#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(5, 14);
    int r = rnd.next(1, n);

    set<pair<int, int>> edgeSet;
    auto addEdge = [&](int a, int b) {
        if (a == b) return;
        if (a > b) swap(a, b);
        edgeSet.insert({a, b});
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) addEdge(center, i);
        int extra = rnd.next(0, n / 2);
        for (int i = 0; i < extra; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else if (mode == 2) {
        int split = rnd.next(2, n - 2);
        for (int i = 1; i < split; ++i) addEdge(i, i + 1);
        for (int i = split + 1; i < n; ++i) addEdge(i, i + 1);
        if (rnd.next(0, 1)) r = rnd.next(split + 1, n);
    } else if (mode == 3) {
        double density = rnd.next(0.35, 0.85);
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                if (rnd.next() < density) addEdge(i, j);
    } else {
        vector<int> order;
        for (int i = 1; i <= n; ++i) order.push_back(i);
        shuffle(order.begin(), order.end());

        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(parent, order[i]);
        }

        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    }

    if (edgeSet.empty()) addEdge(1, 2);

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), r);
    for (auto [u, v] : edges) println(u, v);

    return 0;
}
