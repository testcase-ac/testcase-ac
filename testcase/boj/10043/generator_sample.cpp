#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 5);
    } else if (mode == 1) {
        n = rnd.next(6, 10);
    } else {
        n = rnd.next(8, 14);
    }

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;
    auto addEdge = [&](int a, int b) {
        if (a > b) {
            swap(a, b);
        }
        if (a != b && used.insert({a, b}).second) {
            edges.push_back({a, b});
        }
    };

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            addEdge(1, i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            addEdge(i, rnd.next(1, i - 1));
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = min<int>(10000 - (n - 1), candidates.size());
    int extra = 0;
    if (mode == 2) {
        extra = rnd.next(0, min(extraLimit, n));
    } else if (mode == 3) {
        extra = rnd.next(min(extraLimit, n), extraLimit);
    } else if (mode == 4) {
        extra = min(extraLimit, rnd.next(n, 2 * n));
    }
    for (int i = 0; i < extra; ++i) {
        addEdge(candidates[i].first, candidates[i].second);
    }

    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()));
    for (int i = 1; i <= n; ++i) {
        int cost;
        if (i == n && rnd.next(0, 3) == 0) {
            cost = 10000;
        } else if (rnd.next(0, 4) == 0) {
            cost = rnd.next(1, 20);
        } else {
            cost = rnd.next(1, 10000);
        }

        int radius;
        if (mode == 0) {
            radius = rnd.next(1, min(n, 3));
        } else if (mode == 1) {
            radius = rnd.next(1, n);
        } else if (rnd.next(0, 3) == 0) {
            radius = n;
        } else {
            radius = rnd.next(1, max(1, n / 2));
        }
        println(cost, radius);
    }
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
