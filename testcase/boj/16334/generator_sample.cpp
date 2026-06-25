#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

static vector<int> makePermutation(int n, int mode) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    if (mode == 0) {
        return p;
    }
    if (mode == 1) {
        reverse(p.begin(), p.end());
        return p;
    }
    if (mode == 2) {
        shuffle(p.begin(), p.end());
        return p;
    }
    if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int at = rnd.next(0, n - 1);
            int other = rnd.next(max(0, at - 2), min(n - 1, at + 2));
            swap(p[at], p[other]);
        }
        return p;
    }

    if (n == 1) {
        return p;
    }

    int blockSize = rnd.next(2, min(n, 5));
    for (int l = 0; l < n; l += blockSize) {
        int r = min(n, l + blockSize);
        if (rnd.next(0, 1)) {
            reverse(p.begin() + l, p.begin() + r);
        } else {
            shuffle(p.begin() + l, p.begin() + r);
        }
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(0, 9) == 0) {
        n = 1;
    } else {
        n = rnd.next(2, 14);
    }

    int mode = rnd.next(0, 4);
    vector<int> p = makePermutation(n, mode);

    vector<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (p[i] > p[j]) {
                edges.emplace_back(i + 1, j + 1);
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }

    println(n, static_cast<int>(edges.size()));
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
