#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& seen, vector<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    if (a == b || !seen.insert({a, b}).second) {
        return;
    }
    edges.push_back({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;
    set<pair<int, int>> seen;

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            addEdge(seen, edges, i - 1, i);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            addEdge(seen, edges, 1, i);
        }
        int extra = rnd.next(0, max(0, n / 2));
        for (int it = 0; it < extra; ++it) {
            addEdge(seen, edges, rnd.next(2, n), rnd.next(2, n));
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            addEdge(seen, edges, i - 1, i);
        }
        if (n >= 3) {
            addEdge(seen, edges, 1, n);
        }
        for (int i = 1; i + 2 <= n; ++i) {
            if (rnd.next(2) == 0) {
                addEdge(seen, edges, i, i + 2);
            }
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = 2; i <= split; ++i) {
            addEdge(seen, edges, 1, i);
        }
        for (int i = split + 2; i <= n; ++i) {
            addEdge(seen, edges, split + 1, i);
        }
        addEdge(seen, edges, rnd.next(1, split), rnd.next(split + 1, n));
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(5) == 0) {
                    addEdge(seen, edges, i, j);
                }
            }
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            addEdge(seen, edges, rnd.next(1, i - 1), i);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(100) < 35) {
                    addEdge(seen, edges, i, j);
                }
            }
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                addEdge(seen, edges, i, j);
            }
        }
        int removeLimit = min((int)edges.size() - (n - 1), n);
        int removeCount = rnd.next(0, removeLimit);
        shuffle(edges.begin(), edges.end());
        edges.resize(edges.size() - removeCount);
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
