#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int chooseWeight(int mode) {
    if (mode == 0) {
        return 0;
    }
    if (mode == 1) {
        return rnd.next(0, 3);
    }
    if (mode == 2) {
        return rnd.next(0, 20);
    }
    if (mode == 3) {
        return rnd.any(vector<int>{0, 1, 2, 5, 10, 1000000000});
    }
    return rnd.next(999999990, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 18);
    int shape = rnd.next(0, 4);
    int weightMode = rnd.next(0, 4);

    vector<pair<int, int>> edges;
    if (shape == 0) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (shape == 1) {
        int center = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i != center) {
                edges.push_back({center, i});
            }
        }
    } else if (shape == 2) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({rnd.next(max(0, i - 3), i - 1), i});
        }
    } else if (shape == 3) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            edges.push_back({i - 1, i});
        }
        for (int i = spine; i < n; ++i) {
            edges.push_back({rnd.next(0, spine - 1), i});
        }
    } else {
        for (int i = 1; i < n; ++i) {
            edges.push_back({rnd.next(0, i - 1), i});
        }
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 0);
    shuffle(labels.begin(), labels.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [u, v] : edges) {
        if (rnd.next(0, 1) == 1) {
            swap(u, v);
        }
        println(labels[u], labels[v], chooseWeight(weightMode));
    }

    return 0;
}
