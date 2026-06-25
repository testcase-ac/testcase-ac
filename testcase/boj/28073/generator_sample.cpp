#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 18 : 12);

    char start = rnd.any(alphabet);
    char finish = rnd.next(0, 4) == 0 ? start : rnd.any(alphabet);

    string labels(n, 'A');
    int startPos = rnd.next(n);
    int finishPos = rnd.next(n);
    if (start != finish) {
        while (finishPos == startPos) {
            finishPos = rnd.next(n);
        }
    }
    labels[startPos] = start;
    labels[finishPos] = finish;
    for (int i = 0; i < n; ++i) {
        if (i == startPos || i == finishPos) {
            continue;
        }
        if (rnd.next(0, 5) == 0) {
            labels[i] = start;
        } else if (rnd.next(0, 5) == 0) {
            labels[i] = finish;
        } else {
            labels[i] = rnd.any(alphabet);
        }
    }

    set<pair<int, int>> edgeSet;
    auto addEdge = [&](int u, int v) {
        if (u == v) {
            return;
        }
        if (u > v) {
            swap(u, v);
        }
        edgeSet.insert({u, v});
    };

    if (mode == 0) {
        // No edges: exercises impossible cases and S == E one-node completion.
    } else if (mode == 1) {
        int edges = rnd.next(1, min(4, n * (n - 1) / 2));
        while ((int)edgeSet.size() < edges) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 2) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin(), order.end());
        int pathLen = rnd.next(1, n - 1);
        for (int i = 0; i < pathLen; ++i) {
            addEdge(order[i], order[i + 1]);
        }
        labels[order[0] - 1] = start;
        labels[order[pathLen] - 1] = finish;
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 25) {
                    addEdge(i, j);
                }
            }
        }
    } else if (mode == 4) {
        int hub = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != hub && rnd.next(0, 99) < 70) {
                addEdge(hub, v);
            }
        }
        int extras = rnd.next(0, n / 2);
        while ((int)edgeSet.size() < extras + n / 3) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 55) {
                    addEdge(i, j);
                }
            }
        }
    }

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    println(string(1, start), string(1, finish));
    println(labels);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
