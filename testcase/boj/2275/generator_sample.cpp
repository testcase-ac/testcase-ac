#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
    } else if (mode == 2) {
        n = rnd.next(2, 18);
    } else if (mode == 3) {
        n = rnd.next(3, 18);
    } else {
        n = rnd.next(4, 18);
    }

    vector<int> parent(n, -1);
    vector<int> weight(n, 0);
    vector<int> depth(n, 0);

    auto pickWeight = [&]() {
        int style = rnd.next(0, 5);
        if (style == 0) return 0;
        if (style == 1) return rnd.next(1, 3);
        if (style == 2) return rnd.next(4, 25);
        if (style == 3) return rnd.next(100, 1000);
        if (style == 4) return rnd.next(50000, 150000);
        return rnd.next(1, 1000000);
    };

    for (int v = 1; v < n; ++v) {
        if (mode == 1) {
            parent[v] = v - 1;
        } else if (mode == 2) {
            parent[v] = 0;
        } else if (mode == 3) {
            parent[v] = (v - 1) / 2;
        } else if (mode == 4) {
            parent[v] = (v <= n / 2 ? v - 1 : rnd.next(0, n / 2));
        } else {
            parent[v] = rnd.next(0, v - 1);
        }

        weight[v] = pickWeight();
        depth[v] = depth[parent[v]] + weight[v];
    }

    int height = *max_element(depth.begin(), depth.end());
    int hMode = rnd.next(0, 5);
    int h = 0;
    if (hMode == 0) {
        h = 0;
    } else if (hMode == 1) {
        h = rnd.next(0, min(height, 150000));
    } else if (hMode == 2) {
        h = min(150000, height);
    } else if (hMode == 3) {
        h = min(150000, height + rnd.next(0, 20));
    } else if (hMode == 4) {
        h = rnd.next(0, 150000);
    } else {
        h = 150000;
    }

    vector<int> label(n);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());

    vector<int> outParent(n + 1), outWeight(n + 1);
    for (int v = 0; v < n; ++v) {
        int row = label[v];
        if (parent[v] == -1) {
            outParent[row] = 0;
            outWeight[row] = 0;
        } else {
            outParent[row] = label[parent[v]];
            outWeight[row] = weight[v];
        }
    }

    println(n, h);
    for (int row = 1; row <= n; ++row) {
        println(outParent[row], outWeight[row]);
    }

    return 0;
}
