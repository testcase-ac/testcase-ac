#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i + 1;
    shuffle(order.begin(), order.end());

    vector<pair<int, int>> edges;
    auto addEdgeByRank = [&](int better, int worse) {
        edges.emplace_back(order[better], order[worse]);
    };

    if (mode == 0) {
        for (int i = 0; i + 1 < n; ++i) addEdgeByRank(i, i + 1);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        order.resize(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) addEdgeByRank(i, j);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < split; ++i) {
            for (int j = split; j < n; ++j) {
                if (rnd.next(0, 2) > 0) addEdgeByRank(i, j);
            }
        }
    } else if (mode == 3) {
        int center = rnd.next(0, n - 1);
        bool centerWins = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            if (i == center) continue;
            if (centerWins) {
                addEdgeByRank(min(center, i), max(center, i));
            } else {
                addEdgeByRank(min(i, center), max(i, center));
            }
        }
    } else {
        double probability = rnd.next(0.15, 0.65);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < probability) addEdgeByRank(i, j);
            }
        }
    }

    if (edges.empty()) addEdgeByRank(0, 1);
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) println(edge.first, edge.second);

    return 0;
}
