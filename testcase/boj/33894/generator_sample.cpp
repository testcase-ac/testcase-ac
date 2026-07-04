#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int evenWeight(int mode) {
    if (mode == 0) {
        return 2;
    }
    if (mode == 1) {
        return 2 * rnd.next(1, 6);
    }
    if (mode == 2) {
        return 2 * rnd.next(10, 100);
    }
    return 2 * rnd.next(1, 500000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 18);
    int shape = rnd.next(4);
    int weightMode = rnd.next(4);
    vector<pair<int, int>> edges;

    if (shape == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v});
        }
    } else if (shape == 1) {
        for (int v = 2; v <= n; ++v) {
            edges.push_back({1, v});
        }
    } else if (shape == 2) {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) {
            edges.push_back({v - 1, v});
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.push_back({rnd.next(1, spine), v});
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int parent = rnd.next(1, v - 1);
            edges.push_back({parent, v});
        }
    }

    shuffle(edges.begin(), edges.end());

    vector<int> candidates(n - 1);
    iota(candidates.begin(), candidates.end(), 2);
    shuffle(candidates.begin(), candidates.end());

    int defenderMode = rnd.next(4);
    int k;
    if (defenderMode == 0) {
        k = 1;
    } else if (defenderMode == 1) {
        k = n - 1;
    } else if (defenderMode == 2) {
        k = rnd.next(1, min(n - 1, 4));
    } else {
        k = rnd.next(1, n - 1);
    }
    candidates.resize(k);
    shuffle(candidates.begin(), candidates.end());

    println(n, k);
    for (auto [a, b] : edges) {
        if (rnd.next(2) == 0) {
            swap(a, b);
        }
        println(a, b, evenWeight(weightMode));
    }
    println(candidates);

    return 0;
}
