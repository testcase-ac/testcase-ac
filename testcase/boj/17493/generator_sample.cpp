#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.push_back({center, i});
            }
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        int spine = rnd.next(2, n - 1);
        for (int i = 2; i <= spine; ++i) {
            edges.push_back({i - 1, i});
        }
        for (int i = spine + 1; i <= n; ++i) {
            edges.push_back({rnd.next(1, spine), i});
        }
    } else if (mode == 4) {
        n = rnd.next(3, 14);
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(max(1, i / 3), i - 1), i});
        }
    } else {
        n = rnd.next(2, 14);
        for (int i = 2; i <= n; ++i) {
            if (rnd.next(0, 99) < 65) {
                edges.push_back({rnd.next(1, i - 1), i});
            }
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }

    println(n, static_cast<int>(edges.size()));
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
