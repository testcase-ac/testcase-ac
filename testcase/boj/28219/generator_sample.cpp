#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 40);
    vector<pair<int, int>> edges;
    int diameterWitness = 1;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) edges.push_back({i, i + 1});
        diameterWitness = n - 1;
    } else if (mode == 1) {
        int pathLen = rnd.next(1, n - 1);
        for (int i = 1; i <= pathLen; ++i) edges.push_back({i, i + 1});
        for (int v = pathLen + 2; v <= n; ++v) edges.push_back({1, v});
        diameterWitness = pathLen + (n > pathLen + 1 ? 1 : 0);
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) edges.push_back({v, v / 2});
        int h = 0;
        for (int x = n; x > 1; x /= 2) ++h;
        diameterWitness = max(1, 2 * h - 1);
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) edges.push_back({i, i + 1});
        for (int v = spine + 1; v <= n; ++v) edges.push_back({rnd.next(1, spine), v});
        diameterWitness = spine - 1;
    } else {
        int forcedPath = rnd.next(2, n);
        for (int i = 1; i < forcedPath; ++i) edges.push_back({i, i + 1});
        for (int v = forcedPath + 1; v <= n; ++v) edges.push_back({rnd.next(1, v - 1), v});
        diameterWitness = forcedPath - 1;
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) label[i] = i;
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    int k = rnd.next(1, diameterWitness);
    println(n, k);
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) swap(a, b);
        println(label[a], label[b]);
    }

    return 0;
}
