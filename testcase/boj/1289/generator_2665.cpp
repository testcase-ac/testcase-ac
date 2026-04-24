#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes: allow even N=1
    int N = rnd.next(1, 10);
    vector<pair<int,int>> edges;
    // Generate a random tree via parent pointers
    for (int i = 2; i <= N; ++i) {
        int p = rnd.next(1, i - 1);
        edges.emplace_back(p, i);
    }
    // Randomize edge order
    shuffle(edges.begin(), edges.end());
    // Output
    println(N);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        // random orientation
        if (rnd.next(0,1)) swap(u, v);
        // weight hi then weight in [0,hi], to add diversity
        int hi = rnd.next(0, 1000);
        int w = rnd.next(0, hi);
        println(u, v, w);
    }
    return 0;
}
