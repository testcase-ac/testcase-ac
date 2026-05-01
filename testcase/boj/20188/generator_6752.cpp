#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with variability: small or medium size
    int N;
    if (rnd.next() < 0.3) {
        N = rnd.next(2, 5);
    } else {
        N = rnd.next(6, 20);
    }

    // Choose tree shape type: chain, star, random, or balanced-ish
    int type = rnd.next(0, 3);
    vector<pair<int,int>> edges;

    switch (type) {
        // Chain: a simple path 1-2-3-...-N
        case 0:
            for (int i = 2; i <= N; ++i)
                edges.emplace_back(i - 1, i);
            break;

        // Star: all nodes attached to root 1
        case 1:
            for (int i = 2; i <= N; ++i)
                edges.emplace_back(1, i);
            break;

        // Random tree: attach each new node i to a random parent in [1, i-1]
        case 2:
            for (int i = 2; i <= N; ++i) {
                int p;
                if (rnd.next() < 0.5) {
                    p = rnd.next(1, i - 1);
                } else {
                    // bias towards smaller labels to reduce depth
                    p = rnd.wnext(i - 1, -1) + 1;
                }
                edges.emplace_back(p, i);
            }
            break;

        // Balanced-ish: attach node i to a parent in [1, (i-1)/2]
        case 3:
            for (int i = 2; i <= N; ++i) {
                int maxp = max(1, (i - 1) / 2);
                int p = rnd.next(1, maxp);
                edges.emplace_back(p, i);
            }
            break;
    }

    // Shuffle edge order for additional randomness
    shuffle(edges.begin(), edges.end());

    // Output
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
