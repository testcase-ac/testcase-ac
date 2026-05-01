#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total nodes
    int N = rnd.next(5, 20);
    // Cycle length from 3 to N, biasing towards smaller cycles
    int C = rnd.wnext(N - 2, -1) + 3;

    vector<pair<int,int>> edges;
    // Build the cycle on nodes 1..C
    for (int i = 1; i < C; i++) {
        edges.emplace_back(i, i + 1);
    }
    edges.emplace_back(C, 1);

    // Probability of chaining additional nodes
    double chainProb = rnd.next(); // [0,1)
    // Attach remaining nodes C+1..N as trees
    for (int i = C + 1; i <= N; i++) {
        int parent;
        if (i > C + 1 && rnd.next() < chainProb) {
            // Chain onto the previous tree node for depth
            parent = rnd.next(C + 1, i - 1);
        } else {
            // Attach directly to the cycle
            parent = rnd.next(1, C);
        }
        edges.emplace_back(parent, i);
    }

    // Shuffle edge order for variability
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
