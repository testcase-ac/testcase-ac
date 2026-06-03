#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 2;
    if (mode == 0) {
        n = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(3, 18);
    } else if (mode == 2) {
        n = rnd.next(4, 20);
    } else if (mode == 3) {
        n = rnd.next(5, 24);
    } else if (mode == 4) {
        n = rnd.next(8, 35);
    } else {
        n = rnd.next(2, 50);
    }

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(v - 1, v);
        }
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(1, v);
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(v / 2, v);
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, max(2, n / 2));
        for (int v = 2; v <= spine; ++v) {
            edges.emplace_back(v - 1, v);
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.emplace_back(rnd.next(1, spine), v);
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(rnd.next(1, v - 1), v);
        }
    }

    vector<int> labels(n);
    for (int i = 0; i < n; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());

    shuffle(edges.begin(), edges.end());
    vector<long long> weights;
    for (int i = 0; i < n - 1; ++i) {
        int kind = rnd.next(0, 5);
        if (kind == 0) {
            weights.push_back(1);
        } else if (kind == 1) {
            weights.push_back(rnd.next(1, 9));
        } else if (kind == 2) {
            weights.push_back(rnd.next(10, 1000));
        } else if (kind == 3) {
            weights.push_back(1000000000LL);
        } else if (kind == 4) {
            weights.push_back(rnd.next(999999000, 1000000000));
        } else {
            weights.push_back(rnd.next(1, 1000000000));
        }
    }
    shuffle(weights.begin(), weights.end());

    println(n);
    for (auto [u, v] : edges) {
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(labels[u - 1], labels[v - 1]);
    }
    println(weights);

    return 0;
}
