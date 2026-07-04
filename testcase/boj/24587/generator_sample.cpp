#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, 12);
    int m;
    if (rnd.next(0, 4) == 0) {
        vector<int> specialMods = {1, 2, 9, 10, 11, 97, 100, 1000, 1000000000};
        m = rnd.any(specialMods);
    } else {
        m = rnd.next(1, 1000);
    }
    int q = rnd.next(1, min(20, n * n));

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.push_back({center, i});
            }
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i});
        }
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());
    vector<int> relabel(n + 1);
    for (int i = 1; i <= n; ++i) {
        relabel[i] = labels[i - 1];
    }
    for (auto& edge : edges) {
        edge = {relabel[edge.first], relabel[edge.second]};
        if (rnd.next(0, 1) == 1) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<int> digits(n + 1);
    int digitMode = rnd.next(0, 3);
    for (int i = 1; i <= n; ++i) {
        if (digitMode == 0) {
            digits[i] = rnd.next(0, 9);
        } else if (digitMode == 1) {
            digits[i] = (i + rnd.next(0, 1)) % 10;
        } else if (digitMode == 2) {
            digits[i] = rnd.any(vector<int>{0, 0, 1, 9});
        } else {
            digits[i] = rnd.any(vector<int>{0, 5, 9});
        }
    }

    vector<pair<int, int>> queries;
    queries.push_back({relabel[1], relabel[n]});
    queries.push_back({relabel[n], relabel[1]});
    queries.push_back({relabel[rnd.next(1, n)], relabel[rnd.next(1, n)]});
    queries.push_back({relabel[rnd.next(1, n)], relabel[rnd.next(1, n)]});
    while (static_cast<int>(queries.size()) < q) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (rnd.next(0, 5) == 0) {
            b = a;
        }
        queries.push_back({a, b});
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(q);

    println(n, m, q);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    for (int i = 1; i <= n; ++i) {
        println(digits[i]);
    }
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
