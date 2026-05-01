#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sample N biased towards smaller but allowing up to 15
    int N = rnd.wnext(15, -2) + 1;
    N = max(N, 2);

    // Choose a tree shape: 0=path, 1=star, 2=random, 3=balanced, 4=caterpillar
    int t = rnd.next(0, 4);
    vector<pair<int,int>> edges;

    if (t == 0) {
        // Path
        for (int i = 1; i < N; i++)
            edges.emplace_back(i, i+1);
    } else if (t == 1) {
        // Star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++)
            if (i != center)
                edges.emplace_back(center, i);
    } else if (t == 2) {
        // Uniform random tree
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    } else if (t == 3) {
        // Balanced-like (chain to parent = floor(i/2))
        for (int i = 2; i <= N; i++) {
            int p = i/2;
            edges.emplace_back(p, i);
        }
    } else {
        // Caterpillar: a path of length B, then leaves
        int B = rnd.next(2, N);
        // backbone
        for (int i = 1; i < B; i++)
            edges.emplace_back(i, i+1);
        // attach remaining as leaves
        for (int i = B+1; i <= N; i++) {
            int p = rnd.next(1, B);
            edges.emplace_back(p, i);
        }
    }

    // Shuffle edge order for extra variability
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
