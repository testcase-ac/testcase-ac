#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(3, 14);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int v = 2; v <= n; ++v) edges.push_back({v - 1, v});
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) edges.push_back({1, v});
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) edges.push_back({v / 2, v});
    } else {
        for (int v = 2; v <= n; ++v) edges.push_back({rnd.next(1, v - 1), v});
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) label[i] = i;
    shuffle(label.begin() + 1, label.end());

    set<pair<int, int>> treeEdges;
    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
        treeEdges.insert(minmax(edge.first, edge.second));
    }
    shuffle(edges.begin(), edges.end());

    vector<pair<int, int>> extraEdges;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!treeEdges.count({u, v})) extraEdges.push_back({u, v});
        }
    }
    shuffle(extraEdges.begin(), extraEdges.end());

    int q = rnd.next(4, 12);

    println(n);
    for (const auto& edge : edges) println(edge.first, edge.second);
    println(q);

    for (int i = 0; i < q; ++i) {
        auto added = extraEdges[i % extraEdges.size()];
        if (rnd.next(0, 1)) swap(added.first, added.second);

        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        if (i % 5 == 0) b = a;

        int k;
        if (i % 4 == 0) {
            k = rnd.next(1, 3);
        } else if (i % 4 == 1) {
            k = rnd.next(n, 2 * n + 3);
        } else if (i % 4 == 2) {
            k = rnd.next(1, 2 * n + 3);
            if (k % 2 == 0) ++k;
        } else {
            k = rnd.next(1, 2 * n + 3);
            if (k % 2 == 1) ++k;
        }

        println(added.first, added.second, a, b, k);
    }

    return 0;
}
