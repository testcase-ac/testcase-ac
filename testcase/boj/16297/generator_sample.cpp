#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 9);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else {
        n = rnd.next(8, 14);
    }

    vector<int> value(n);
    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (valueMode == 0) {
            value[i] = rnd.next(0, 10);
        } else if (valueMode == 1) {
            value[i] = (rnd.next(0, 3) == 0 ? 0 : rnd.next(1, 100));
        } else if (valueMode == 2) {
            value[i] = rnd.next(900000000, 1000000000);
        } else {
            value[i] = (i % 2 == 0 ? rnd.next(0, 5) : rnd.next(50, 200));
        }
    }

    set<pair<int, int>> edgeSet;
    auto addEdge = [&](int from, int to) {
        if (from != to) {
            edgeSet.insert({from, to});
        }
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i - 1, i);
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            addEdge(rnd.next(0, i - 1), i);
        }
    } else if (mode == 2) {
        vector<int> layer(n);
        layer[0] = 0;
        for (int i = 1; i < n; ++i) {
            layer[i] = rnd.next(1, 3);
        }
        for (int i = 1; i < n; ++i) {
            vector<int> parents;
            for (int j = 0; j < i; ++j) {
                if (layer[j] < layer[i]) {
                    parents.push_back(j);
                }
            }
            addEdge(parents.empty() ? 0 : rnd.any(parents), i);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (layer[i] < layer[j] && rnd.next(0, 99) < 25) {
                    addEdge(i, j);
                }
            }
        }
    } else {
        for (int i = 1; i < n; ++i) {
            addEdge(rnd.next(0, i - 1), i);
        }
        int percent = rnd.next(20, 70);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(0, 99) < percent) {
                    addEdge(i, j);
                }
            }
        }
    }

    vector<pair<int, int>> edges(edgeSet.begin(), edgeSet.end());
    shuffle(edges.begin(), edges.end());

    println(n, int(edges.size()));
    println(value);
    for (auto [from, to] : edges) {
        println(from, to);
    }

    return 0;
}
