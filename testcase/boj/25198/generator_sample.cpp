#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 0 ? 1 : rnd.next(2, 14);
    vector<pair<int, int>> edges;

    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.push_back({center, i});
            }
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 2; i <= spine; ++i) {
            edges.push_back({i - 1, i});
        }
        for (int i = spine + 1; i <= n; ++i) {
            int attach = rnd.next(1, spine);
            edges.push_back({attach, i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            edges.push_back({parent, i});
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());
    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    int s = rnd.next(1, n);
    int c = rnd.next(1, n);
    int h = rnd.next(1, n);
    if (n > 1 && rnd.next(0, 4) == 0) {
        int shared = rnd.next(1, n);
        if (rnd.next(0, 1)) {
            s = shared;
        } else {
            c = shared;
        }
        h = shared;
    }

    println(n);
    println(s, c, h);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
