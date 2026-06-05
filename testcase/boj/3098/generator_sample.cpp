#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 50);
    } else if (mode == 1) {
        n = rnd.next(3, 50);
    } else {
        n = rnd.next(2, 20);
    }

    set<pair<int, int>> edgeSet;
    vector<pair<int, int>> edges;
    auto addEdge = [&](int a, int b) {
        if (a > b) {
            swap(a, b);
        }
        if (a == b || !edgeSet.insert({a, b}).second) {
            return;
        }
        edges.push_back({a, b});
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                addEdge(center, v);
            }
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                addEdge(i, j);
            }
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            addEdge(v, rnd.next(1, v - 1));
        }

        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (!edgeSet.count({i, j})) {
                    candidates.push_back({i, j});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int extra = rnd.next(0, (int)candidates.size());
        for (int i = 0; i < extra; ++i) {
            addEdge(candidates[i].first, candidates[i].second);
        }
    } else if (mode == 4) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i <= split; ++i) {
            for (int j = i + 1; j <= split; ++j) {
                if (rnd.next(0, 3) != 0) {
                    addEdge(i, j);
                }
            }
        }
        for (int i = split + 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 3) != 0) {
                    addEdge(i, j);
                }
            }
        }
        for (int i = 1; i < split; ++i) {
            addEdge(i, i + 1);
        }
        for (int i = split + 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
        addEdge(rnd.next(1, split), rnd.next(split + 1, n));
    } else {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            addEdge(i, i + 1);
        }
        for (int v = spine + 1; v <= n; ++v) {
            addEdge(rnd.next(1, spine), v);
        }
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            addEdge(rnd.next(1, n), rnd.next(1, n));
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
