#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 15);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(v - 1, v);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.emplace_back(center, v);
            }
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) {
            edges.emplace_back(v - 1, v);
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.emplace_back(rnd.next(1, spine), v);
        }
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(v / 2, v);
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(rnd.next(1, v - 1), v);
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    int weightMode = rnd.next(0, 3);
    println(n);
    for (auto [u, v] : edges) {
        int length;
        if (weightMode == 0) {
            length = 1;
        } else if (weightMode == 1) {
            length = rnd.next(1, 20);
        } else if (weightMode == 2) {
            length = rnd.next(39950, 40000);
        } else {
            length = rnd.any(vector<int>{1, 2, 3, 9999, 10000, 40000});
        }

        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(label[u], label[v], length);
    }

    return 0;
}
