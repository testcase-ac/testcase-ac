#include "testlib.h"
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int mode = rnd.next(0, 3);
    vector<pair<int, int>> edges;

    for (int v = 2; v <= n; ++v) {
        int parent;
        if (mode == 0) {
            parent = 1;
        } else if (mode == 1) {
            parent = v - 1;
        } else if (mode == 2) {
            parent = rnd.next(1, v - 1);
        } else {
            parent = n == 2 || v <= (n + 1) / 2 ? 1 : rnd.next(2, (n + 1) / 2);
        }
        edges.emplace_back(parent, v);
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto [u, v] : edges) {
        if (rnd.next(2)) swap(u, v);
        println(label[u], label[v]);
    }
}
