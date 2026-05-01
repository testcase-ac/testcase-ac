#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rooms
    int n = rnd.next(2, 12);

    // Create a random spanning tree to ensure connectivity
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    vector<array<int,3>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({nodes[i-1], nodes[i], 0});
    }

    // Add a few extra edges (could be multi-edges or self-loops)
    int extras = rnd.wnext(n, -1);
    for (int i = 0; i < extras; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        edges.push_back({u, v, 0});
    }

    // With some probability, add a direct edge from 1 to n
    if (rnd.next(0, 9) < 3) {
        edges.push_back({1, n, 0});
    }

    int m = edges.size();

    // Decide on color range: narrow or wide
    bool narrow = rnd.next(0, 1) == 0;
    int cmin, cmax;
    if (narrow) {
        cmin = rnd.next(1, 100);
        cmax = cmin + rnd.next(0, 5);
    } else {
        cmin = 1;
        cmax = 1000000000;
    }

    // Assign colors
    for (auto &e : edges) {
        e[2] = rnd.next(cmin, cmax);
    }

    // Shuffle edges before output
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, m);
    for (auto &e : edges) {
        println(e[0], e[1], e[2]);
    }

    return 0;
}
