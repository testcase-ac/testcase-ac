#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 14);
    vector<int> parent(n, 0);

    if (mode == 0) {
        for (int v = 1; v < n; ++v) parent[v] = v - 1;
    } else if (mode == 1) {
        for (int v = 1; v < n; ++v) parent[v] = 0;
    } else if (mode == 2) {
        for (int v = 1; v < n; ++v) parent[v] = (v - 1) / 2;
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int v = 1; v < spine; ++v) parent[v] = v - 1;
        for (int v = spine; v < n; ++v) parent[v] = rnd.next(0, spine - 1);
    } else {
        for (int v = 1; v < n; ++v) parent[v] = rnd.next(0, v - 1);
    }

    vector<int> depth(n, 0);
    for (int v = 1; v < n; ++v) depth[v] = depth[parent[v]] + 1;
    int maxDepth = *max_element(depth.begin(), depth.end());

    int kMode = rnd.next(4);
    int k = 0;
    if (kMode == 0) {
        k = 0;
    } else if (kMode == 1) {
        k = maxDepth;
    } else if (kMode == 2) {
        k = rnd.next(0, maxDepth);
    } else {
        k = rnd.next(0, n - 1);
    }

    vector<int> apples(n, 0);
    int appleMode = rnd.next(5);
    for (int v = 0; v < n; ++v) {
        if (appleMode == 0) {
            apples[v] = rnd.next(2);
        } else if (appleMode == 1) {
            apples[v] = depth[v] <= k;
        } else if (appleMode == 2) {
            apples[v] = depth[v] > k;
        } else if (appleMode == 3) {
            apples[v] = (v % 2 == 0);
        } else {
            apples[v] = (v == 0 || v == n - 1);
        }
    }

    vector<pair<int, int>> edges;
    for (int v = 1; v < n; ++v) edges.push_back({parent[v], v});
    shuffle(edges.begin(), edges.end());

    println(n, k);
    for (const auto& edge : edges) println(edge.first, edge.second);
    println(apples);

    return 0;
}
