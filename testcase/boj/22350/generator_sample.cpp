#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    int treeMode = rnd.next(0, 2);
    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; ++v) {
        int parent = treeMode == 0 ? v - 1
                   : treeMode == 1 ? 1
                                   : rnd.next(1, v - 1);
        edges.emplace_back(parent, v);
    }
    shuffle(edges.begin(), edges.end());

    println(n, m);
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) swap(a, b);
        println(a, b);
    }
    for (int i = 0; i < m; ++i) {
        int distanceMode = rnd.next(0, 2);
        int d = distanceMode == 0 ? 0
              : distanceMode == 1 ? n - 1
                                  : rnd.next(0, n - 1);
        int g = rnd.next(0, 9) == 0 ? 1000000000 : rnd.next(1, 100);
        println(rnd.next(1, n), d, g);
    }
}
