#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 3);
        for (int i = 1; i < n; ++i) {
            edges.emplace_back(i, i + 1);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        for (int i = 1; i < n; ++i) {
            edges.emplace_back(i, i + 1);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.emplace_back(center, v);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 31);
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(v / 2, v);
        }
    } else if (mode == 4) {
        n = rnd.next(4, 35);
        int handle = rnd.next(2, n - 1);
        for (int i = 1; i < handle; ++i) {
            edges.emplace_back(i, i + 1);
        }
        for (int v = handle + 1; v <= n; ++v) {
            edges.emplace_back(handle, v);
        }
    } else if (mode == 5) {
        n = rnd.next(4, 36);
        int left = rnd.next(2, n - 1);
        int right = left + 1;
        edges.emplace_back(left, right);
        for (int v = 1; v <= n; ++v) {
            if (v == left || v == right) {
                continue;
            }
            edges.emplace_back(rnd.next(0, 1) == 0 ? left : right, v);
        }
    } else if (mode == 6) {
        n = rnd.next(5, 35);
        int spine = rnd.next(2, min(n, 12));
        for (int i = 1; i < spine; ++i) {
            edges.emplace_back(i, i + 1);
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.emplace_back(rnd.next(1, spine), v);
        }
    } else {
        n = rnd.next(2, 40);
        for (int v = 2; v <= n; ++v) {
            int parentBias = rnd.next(0, 2);
            int parent = parentBias == 0 ? rnd.next(1, v - 1) : rnd.wnext(v - 1, -2) + 1;
            edges.emplace_back(parent, v);
        }
    }

    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin() + 1, perm.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        println(perm[a], perm[b]);
    }

    return 0;
}
