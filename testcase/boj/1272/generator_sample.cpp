#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (rnd.next(10) == 0) {
        n = rnd.next(80, 160);
    } else {
        n = rnd.next(1, 35);
    }

    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());

    int root = label[0];
    vector<int> weight(n + 1, 0);
    vector<pair<int, int>> edges;
    weight[root] = rnd.next(1, 20);

    for (int i = 1; i < n; ++i) {
        int parentIndex = 0;
        if (mode == 0) {
            parentIndex = 0;
        } else if (mode == 1) {
            parentIndex = i - 1;
        } else if (mode == 2) {
            parentIndex = (i < n / 2 ? i - 1 : rnd.next(0, max(0, n / 2 - 1)));
        } else if (mode == 3) {
            parentIndex = (i - 1) / 2;
        } else {
            parentIndex = rnd.next(0, i - 1);
        }

        int parent = label[parentIndex];
        int child = label[i];
        int step = rnd.next(1, mode == 1 ? 4 : 40);
        weight[child] = min(50000, weight[parent] + step);
        edges.push_back({parent, child});
    }

    shuffle(edges.begin(), edges.end());

    println(n, root);
    vector<int> outputWeights;
    for (int i = 1; i <= n; ++i) {
        outputWeights.push_back(weight[i]);
    }
    println(outputWeights);
    for (auto [u, v] : edges) {
        if (rnd.next(2) == 0) {
            swap(u, v);
        }
        println(u, v);
    }

    return 0;
}
