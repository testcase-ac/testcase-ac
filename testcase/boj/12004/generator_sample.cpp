#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({i, i + 1});
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i});
        }
        int extra = rnd.next(0, min(12, n * (n - 1) / 2 - (n - 1)));
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n - 1);
            if (b >= a) ++b;
            edges.push_back({a, b});
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) {
            if (rnd.next(0, 1)) edges.push_back({i, i + 1});
        }
        for (int i = split + 1; i < n; ++i) {
            if (rnd.next(0, 1)) edges.push_back({i, i + 1});
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 2) > 0) edges.push_back({i, j});
            }
        }
    } else if (mode == 4) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        int copies = rnd.next(1, 10);
        for (int i = 0; i < copies; ++i) {
            edges.push_back({a, b});
        }
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) ++v;
            edges.push_back({u, v});
        }
    } else {
        int hub = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != hub) edges.push_back({hub, i});
        }
        int tail = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != tail && rnd.next(0, 2) == 0) edges.push_back({tail, i});
        }
    }

    if (edges.empty()) {
        edges.push_back({1, 2});
    }

    shuffle(edges.begin(), edges.end());
    int m = min<int>(3000, edges.size());
    edges.resize(m);

    vector<int> order;
    for (int i = 1; i <= n; ++i) {
        order.push_back(i);
    }

    int orderMode = rnd.next(0, 3);
    if (orderMode == 0) {
        shuffle(order.begin(), order.end());
    } else if (orderMode == 1) {
        reverse(order.begin(), order.end());
    } else if (orderMode == 2) {
        rotate(order.begin(), order.begin() + rnd.next(0, n - 1), order.end());
    }

    println(n, m);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }
    for (int barn : order) {
        println(barn);
    }

    return 0;
}
