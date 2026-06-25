#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using Edge = tuple<int, int, int, int>;

int smallValue() {
    int mode = rnd.next(4);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return rnd.next(1, 5);
    }
    if (mode == 2) {
        return rnd.next(6, 30);
    }
    return rnd.next(999999990, 1000000000);
}

long long energyValue() {
    int mode = rnd.next(5);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return rnd.next(1, 30);
    }
    if (mode == 2) {
        return rnd.next(31, 1000);
    }
    if (mode == 3) {
        return rnd.next(1000000000LL, 1000001000LL);
    }
    return rnd.next(999999999999999000LL, 1000000000000000000LL);
}

pair<int, int> randomQueryEndpoints(int n) {
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) {
        ++b;
    }
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 12);
    vector<Edge> edges;

    for (int v = 2; v <= n; ++v) {
        int parent;
        if (mode == 0) {
            parent = v - 1;
        } else if (mode == 1) {
            parent = 1;
        } else if (mode == 2) {
            parent = max(1, v / 2);
        } else {
            parent = rnd.next(1, v - 1);
        }

        int r = smallValue();
        int z = smallValue();
        if (mode == 3 && rnd.next(2) == 0) {
            z = 1;
        }
        if (mode == 4 && rnd.next(3) == 0) {
            r = 1000000000;
        }
        edges.emplace_back(parent, v, r, z);
    }

    if (mode >= 3) {
        vector<int> perm(n + 1);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin() + 1, perm.end());
        for (auto& [x, y, r, z] : edges) {
            x = perm[x];
            y = perm[y];
        }
    }

    shuffle(edges.begin(), edges.end());

    int q = rnd.next(1, 12);
    vector<tuple<int, int, long long>> queries;
    vector<pair<int, int>> directed;
    directed.reserve(edges.size() * 2);
    for (const auto& [x, y, r, z] : edges) {
        directed.emplace_back(x, y);
        directed.emplace_back(y, x);
    }
    shuffle(directed.begin(), directed.end());

    for (int i = 0; i < q; ++i) {
        int a, b;
        if (i < static_cast<int>(directed.size()) && rnd.next(3) == 0) {
            tie(a, b) = directed[i];
        } else {
            tie(a, b) = randomQueryEndpoints(n);
        }
        queries.emplace_back(a, b, energyValue());
    }

    println(n);
    for (const auto& [x, y, r, z] : edges) {
        println(x, y, r, z);
    }
    println(q);
    for (const auto& [a, b, e] : queries) {
        println(a, b, e);
    }

    return 0;
}
