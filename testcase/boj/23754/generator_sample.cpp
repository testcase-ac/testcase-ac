#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 3 ? 12 : 18);
    int quotaX = rnd.next(1, 200);
    int quotaY = rnd.next(1, 200);

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b) {
        if (a != b && used.insert({a, b}).second) {
            edges.push_back({a, b});
        }
    };

    if (mode == 0) {
        // No precedence constraints.
    } else if (mode == 1) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());
        int m = rnd.next(0, min(n * (n - 1) / 2, 35));
        vector<pair<int, int>> candidates;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                candidates.push_back({p[i], p[j]});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < m && i < (int)candidates.size(); ++i) {
            addEdge(candidates[i].first, candidates[i].second);
        }
    } else if (mode == 2) {
        int layers = rnd.next(2, min(5, max(2, n)));
        vector<int> layer(n + 1);
        for (int i = 1; i <= n; ++i) layer[i] = rnd.next(0, layers - 1);
        layer[1] = 0;
        layer[n] = layers - 1;
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (layer[a] < layer[b] && rnd.next(0, 99) < 45) {
                    addEdge(a, b);
                }
            }
        }
    } else if (mode == 3 && n >= 2) {
        int cycleSize = rnd.next(2, min(n, 5));
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());
        for (int i = 0; i < cycleSize; ++i) {
            addEdge(p[i], p[(i + 1) % cycleSize]);
        }
        int extra = rnd.next(0, min(20, n * (n - 1) - (int)edges.size()));
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (a != b && !used.count({a, b})) candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < extra; ++i) {
            addEdge(candidates[i].first, candidates[i].second);
        }
    } else if (mode == 4) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
        int extra = rnd.next(0, min(20, n * (n - 1) - (int)edges.size()));
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (!used.count({a, b})) candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        extra = min(extra, (int)candidates.size());
        for (int i = 0; i < extra; ++i) {
            addEdge(candidates[i].first, candidates[i].second);
        }
    } else {
        int m = rnd.next(0, min(n * (n - 1), 45));
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                if (a != b) candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < m; ++i) {
            addEdge(candidates[i].first, candidates[i].second);
        }
    }

    vector<pair<int, int>> sales(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 99) < 20) {
            sales[i] = {rnd.next(1, 8), rnd.next(1, 8)};
        } else if (rnd.next(0, 99) < 35) {
            sales[i] = {rnd.next(100, 200), rnd.next(1, 200)};
        } else {
            sales[i] = {rnd.next(1, 200), rnd.next(1, 200)};
        }
    }

    println(n, (int)edges.size(), quotaX, quotaY);
    for (auto [a, b] : edges) {
        println(a, b);
    }
    for (auto [x, y] : sales) {
        println(x, y);
    }
}
