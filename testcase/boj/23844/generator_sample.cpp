#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    int k = 1;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, n);
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v});
        }
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        k = rnd.next(1, min(n, 4));
        for (int v = 2; v <= n; ++v) {
            edges.push_back({v - 1, v});
        }
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        k = rnd.any(vector<int>{1, rnd.next(2, n), n});
        for (int v = 2; v <= n; ++v) {
            edges.push_back({1, v});
        }
    } else if (mode == 3) {
        int spine = rnd.next(3, 9);
        int leaves = rnd.next(2, 10);
        n = spine + leaves;
        k = rnd.next(1, min(n, max(2, leaves + 1)));
        for (int v = 2; v <= spine; ++v) {
            edges.push_back({v - 1, v});
        }
        for (int i = 0; i < leaves; ++i) {
            edges.push_back({rnd.next(1, spine), spine + 1 + i});
        }
    } else if (mode == 4) {
        n = rnd.next(7, 31);
        k = rnd.next(1, min(n, 8));
        for (int v = 2; v <= n; ++v) {
            int parent = max(1, v / 2 + rnd.next(-1, 1));
            parent = min(parent, v - 1);
            edges.push_back({parent, v});
        }
    } else {
        int levels = rnd.next(3, 6);
        vector<vector<int>> byLevel(1, vector<int>{1});
        n = 1;
        for (int level = 1; level < levels; ++level) {
            int width = rnd.next(1, 6);
            byLevel.push_back({});
            for (int i = 0; i < width; ++i) {
                byLevel.back().push_back(++n);
                edges.push_back({rnd.any(byLevel[level - 1]), n});
            }
        }
        k = rnd.next(1, min(n, 6));
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 2, label.end());

    shuffle(edges.begin(), edges.end());
    println(n, k);
    for (auto edge : edges) {
        int a = label[edge.first];
        int b = label[edge.second];
        if (rnd.next(2)) {
            swap(a, b);
        }
        println(a, b);
    }

    return 0;
}
