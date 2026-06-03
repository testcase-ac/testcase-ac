#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Dsu {
    vector<int> parent;

    explicit Dsu(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        parent[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, mode == 4 ? 18 : 12);
    int maxEdges = n * (n - 1) / 2;
    int extraLimit = maxEdges - (n - 1);
    int extraEdges = 0;
    if (mode == 1) {
        extraEdges = rnd.next(0, min(extraLimit, n));
    } else if (mode == 2) {
        extraEdges = rnd.next(max(0, extraLimit / 3), extraLimit);
    } else if (mode == 4) {
        extraEdges = rnd.next(0, min(extraLimit, 30));
    } else {
        extraEdges = rnd.next(0, min(extraLimit, n / 2 + 2));
    }
    int m = n - 1 + extraEdges;
    long long k = rnd.any(vector<long long>{1, 2, 5, 10, 25, 100, 1000, 1000000000LL});

    vector<pair<int, int>> tree;
    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            tree.push_back({i, i + 1});
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            tree.push_back({1, i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            tree.push_back({rnd.next(1, i - 1), i});
        }
    }

    set<pair<int, int>> used;
    vector<pair<int, int>> chosen;
    for (auto [a, b] : tree) {
        if (a > b) {
            swap(a, b);
        }
        used.insert({a, b});
        chosen.push_back({a, b});
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
    for (int i = 0; i < extraEdges; ++i) {
        chosen.push_back(candidates[i]);
    }
    shuffle(chosen.begin(), chosen.end());

    println(n, m, k);
    for (auto [a, b] : chosen) {
        int c;
        int t;
        if (mode == 0) {
            c = rnd.next(1, 5);
            t = rnd.next(1, 8);
        } else if (mode == 1) {
            c = rnd.any(vector<int>{1, 1, 2, 10, 1000});
            t = rnd.next(1, 1000);
        } else if (mode == 2) {
            c = rnd.next(1, 1000);
            t = rnd.next(1, 5);
        } else if (mode == 3) {
            c = rnd.next(1, 20);
            t = rnd.any(vector<int>{1, 2, 3, 1000});
        } else {
            c = rnd.next(900, 1000);
            t = rnd.next(900, 1000);
        }
        println(a, b, c, t);
    }

    return 0;
}
