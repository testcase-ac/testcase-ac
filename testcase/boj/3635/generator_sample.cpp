#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 30);
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i - 1, i);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int v = 1; v <= n; ++v) {
            if (v != center) {
                edges.emplace_back(center, v);
            }
        }
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) {
            edges.emplace_back(v / 2, v);
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int v = 2; v <= spine; ++v) {
            edges.emplace_back(v - 1, v);
        }
        for (int v = spine + 1; v <= n; ++v) {
            edges.emplace_back(rnd.next(1, spine), v);
        }
    } else if (mode == 4) {
        int leftCenter = 1;
        int rightCenter = 2;
        edges.emplace_back(leftCenter, rightCenter);
        for (int v = 3; v <= n; ++v) {
            if (rnd.next(0, 1) == 0) {
                edges.emplace_back(leftCenter, v);
            } else {
                edges.emplace_back(rightCenter, v);
            }
        }
    } else {
        for (int v = 2; v <= n; ++v) {
            int parent = rnd.next(1, v - 1);
            edges.emplace_back(parent, v);
        }
    }

    vector<int> labels(n);
    for (int i = 0; i < n; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());

    for (auto& edge : edges) {
        edge.first = labels[edge.first - 1];
        edge.second = labels[edge.second - 1];
        if (rnd.next(0, 1) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
