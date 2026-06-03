#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 14);

    vector<int> parent(n + 1, 0);
    for (int node = 2; node <= n; ++node) {
        if (mode == 0) {
            parent[node] = node - 1;
        } else if (mode == 1) {
            parent[node] = 1;
        } else if (mode == 2) {
            parent[node] = node / 2;
        } else if (mode == 3) {
            int blockStart = max(1, node - rnd.next(1, min(4, node - 1)));
            parent[node] = rnd.next(blockStart, node - 1);
        } else {
            parent[node] = rnd.next(1, node - 1);
        }
    }

    int maxColor = rnd.next(1, min(n, 5));
    vector<int> color(n + 1, 0);
    color[1] = rnd.next(0, maxColor);
    for (int node = 2; node <= n; ++node) {
        if (color[parent[node]] != 0) {
            if (rnd.next(0, 99) < 55) {
                color[node] = color[parent[node]];
            } else {
                color[node] = rnd.next(1, maxColor);
            }
        } else if (rnd.next(0, 99) < 35) {
            color[node] = 0;
        } else {
            color[node] = rnd.next(1, maxColor);
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 2, label.end());

    vector<int> labeledColor(n + 1);
    for (int node = 1; node <= n; ++node) {
        labeledColor[label[node]] = color[node];
    }

    vector<pair<int, int>> edges;
    for (int node = 2; node <= n; ++node) {
        int a = label[parent[node]];
        int b = label[node];
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        edges.push_back({a, b});
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    vector<int> outputColor;
    outputColor.reserve(n);
    for (int node = 1; node <= n; ++node) {
        outputColor.push_back(labeledColor[node]);
    }
    println(outputColor);
    for (auto [a, b] : edges) {
        println(a, b);
    }

    return 0;
}
