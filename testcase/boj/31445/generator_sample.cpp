#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);

    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i + 1;
    }
    shuffle(order.begin(), order.end());

    set<pair<int, int>> edgeSet;
    auto addEdgeByPosition = [&](int fromPos, int toPos) {
        if (fromPos < toPos) {
            edgeSet.insert({order[fromPos], order[toPos]});
        }
    };

    if (mode == 0) {
        int len = rnd.next(2, n);
        for (int i = 0; i + 1 < len; ++i) {
            addEdgeByPosition(i, i + 1);
        }
    } else if (mode == 1) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i + 1 < split; ++i) {
            addEdgeByPosition(i, i + 1);
        }
        for (int i = split; i + 1 < n; ++i) {
            addEdgeByPosition(i, i + 1);
        }
    } else if (mode == 2) {
        int layers = rnd.next(2, min(n, 5));
        vector<int> layer(n);
        for (int i = 0; i < n; ++i) {
            layer[i] = i * layers / n;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (layer[i] < layer[j] && rnd.next(0, 99) < 45) {
                    addEdgeByPosition(i, j);
                }
            }
        }
    } else if (mode == 3) {
        int anchor = rnd.next(0, n - 2);
        for (int j = anchor + 1; j < n; ++j) {
            if (rnd.next(0, 99) < 70) {
                addEdgeByPosition(anchor, j);
            }
        }
        for (int i = 0; i < anchor; ++i) {
            if (rnd.next(0, 99) < 45) {
                addEdgeByPosition(i, anchor);
            }
        }
    } else {
        int probability = rnd.next(15, 75);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(0, 99) < probability) {
                    addEdgeByPosition(i, j);
                }
            }
        }
    }

    if (edgeSet.empty()) {
        addEdgeByPosition(0, 1);
    }

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
