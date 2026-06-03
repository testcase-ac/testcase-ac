#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int otherNode(int n, int x) {
    int y = rnd.next(1, n - 1);
    if (y >= x) ++y;
    return y;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> ops;

    if (mode == 0) {
        int m = rnd.next(2, 35);
        int u = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            ops.push_back({u, otherNode(n, u)});
        }
    } else if (mode == 1) {
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        int len = rnd.next(2, n);
        for (int i = 0; i + 1 < len; ++i) {
            ops.push_back({nodes[i], nodes[i + 1]});
            if (rnd.next(0, 1)) ops.push_back({nodes[i], otherNode(n, nodes[i])});
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        int m = rnd.next(2, 40);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 1)) {
                ops.push_back({otherNode(n, center), center});
            } else {
                ops.push_back({center, otherNode(n, center)});
            }
        }
    } else if (mode == 3) {
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        int len = rnd.next(2, n);
        for (int i = 0; i < len; ++i) {
            ops.push_back({nodes[i], nodes[(i + 1) % len]});
        }
        if (rnd.next(0, 1)) reverse(ops.begin(), ops.end());
    } else if (mode == 4) {
        int m = rnd.next(2, 50);
        for (int i = 0; i < m; ++i) {
            int u = rnd.next(1, n);
            ops.push_back({u, otherNode(n, u)});
        }
    } else {
        int m = rnd.next(2, 45);
        int a = rnd.next(1, n);
        int b = otherNode(n, a);
        for (int i = 0; i < m; ++i) {
            if (i % 3 == 0) {
                ops.push_back({a, b});
            } else if (i % 3 == 1) {
                ops.push_back({b, a});
            } else {
                int u = rnd.next(1, n);
                ops.push_back({u, otherNode(n, u)});
            }
        }
    }

    if ((int)ops.size() < 2) {
        int u = rnd.next(1, n);
        ops.push_back({u, otherNode(n, u)});
        int v = otherNode(n, u);
        ops.push_back({v, u});
    }

    println(n, (int)ops.size());
    for (auto [u, v] : ops) println(u, v);

    return 0;
}
