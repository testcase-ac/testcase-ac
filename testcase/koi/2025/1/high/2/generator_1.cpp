#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = rnd.next(3, 5);
    } else if (sizeMode == 1) {
        n = rnd.next(6, 10);
    } else if (sizeMode == 2) {
        n = rnd.next(11, 20);
    } else if (sizeMode == 3) {
        n = rnd.next(21, 45);
    } else {
        n = rnd.next(46, 80);
    }

    vector<tuple<int, int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int x, int y, int t) {
        if (x == y) return;
        if ((int)edges.size() >= 4000) return;
        if (used.insert({x, y}).second) {
            edges.push_back({x, y, t});
        }
    };

    auto smallWeight = [&]() {
        int mode = rnd.next(0, 4);
        if (mode == 0) return 1;
        if (mode == 1) return rnd.next(2, 8);
        if (mode == 2) return rnd.next(9, 30);
        if (mode == 3) return rnd.next(31, 300);
        return rnd.next(1000, 100000);
    };

    int graphMode = rnd.next(0, 5);
    if (graphMode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, smallWeight());
        }
    } else if (graphMode == 1) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, smallWeight());
        }
        for (int i = 2; i <= n; ++i) {
            addEdge(i, rnd.next(1, i - 1), smallWeight());
        }
    } else if (graphMode == 2) {
        int hub = rnd.next(2, n - 1);
        for (int i = 1; i <= n; ++i) {
            if (i != hub) {
                addEdge(hub, i, smallWeight());
                addEdge(i, hub, smallWeight());
            }
        }
    } else if (graphMode == 3) {
        int split = rnd.next(2, n - 1);
        for (int i = 1; i < split; ++i) {
            addEdge(i, rnd.next(i + 1, split), smallWeight());
        }
        for (int i = split + 1; i <= n; ++i) {
            addEdge(rnd.next(split, i - 1), i, smallWeight());
        }
    } else {
        addEdge(1, n, smallWeight());
        int paths = rnd.next(1, min(5, n - 2));
        vector<int> mid;
        for (int i = 2; i < n; ++i) mid.push_back(i);
        shuffle(mid.begin(), mid.end());
        for (int i = 0; i < paths; ++i) {
            addEdge(1, mid[i], smallWeight());
            addEdge(mid[i], n, smallWeight());
        }
    }

    int targetM;
    int maxDirected = n * (n - 1);
    if (rnd.next(0, 4) == 0) {
        targetM = rnd.next(3, min(4000, maxDirected));
    } else {
        int extra = rnd.next(0, min(3 * n, 4000));
        targetM = min({4000, maxDirected, max(3, (int)edges.size() + extra)});
    }

    int attempts = 0;
    while ((int)edges.size() < targetM && attempts < targetM * 20 + 200) {
        ++attempts;
        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        addEdge(x, y, smallWeight());
    }
    for (int x = 1; (int)edges.size() < 3 && x <= n; ++x) {
        for (int y = 1; (int)edges.size() < 3 && y <= n; ++y) {
            addEdge(x, y, smallWeight());
        }
    }

    shuffle(edges.begin(), edges.end());

    vector<int> c(n, 0);
    int windowMode = rnd.next(0, 4);
    for (int i = 2; i < n; ++i) {
        int idx = i - 1;
        if (windowMode == 0) {
            c[idx] = 0;
        } else if (windowMode == 1) {
            c[idx] = 1;
        } else if (windowMode == 2) {
            c[idx] = rnd.next(0, 1);
        } else if (windowMode == 3) {
            c[idx] = (i % 2);
        } else {
            c[idx] = (rnd.next(0, 99) < 25 ? 1 : 0);
        }
    }

    long long a;
    long long b;
    int timeMode = rnd.next(0, 5);
    if (timeMode == 0) {
        a = 1;
        b = 1;
    } else if (timeMode == 1) {
        a = rnd.next(2, 6);
        b = rnd.next(1, 12);
    } else if (timeMode == 2) {
        a = rnd.next(7, 30);
        b = rnd.next(7, 30);
    } else if (timeMode == 3) {
        a = rnd.next(1, 100);
        b = rnd.next(1000, 100000);
    } else if (timeMode == 4) {
        a = rnd.next(1000, 100000);
        b = rnd.next(1, 100);
    } else {
        a = rnd.next(1, 1000000000);
        b = rnd.next(1, 1000000000);
    }

    println(n, (int)edges.size());
    for (auto [x, y, t] : edges) {
        println(x, y, t);
    }
    println(c);
    println(a, b);

    return 0;
}
