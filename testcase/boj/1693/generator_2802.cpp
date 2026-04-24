#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small n for hand-checkable
    int n = rnd.next(1, 10);
    vector<pair<int,int>> edges;
    if (n >= 2) {
        // hyperparameters for structure diversity
        double pathProb = 0.33, starProb = 0.33;
        if (rnd.next() < pathProb) {
            // path: 1-2-3-...-n
            for (int i = 1; i < n; ++i)
                edges.emplace_back(i, i+1);
        }
        else if (rnd.next() < starProb) {
            // star: random center
            int center = rnd.next(1, n);
            for (int i = 1; i <= n; ++i)
                if (i != center)
                    edges.emplace_back(center, i);
        }
        else {
            // random tree via random parents with depth bias
            int bias = rnd.next(-1, 1);
            for (int i = 2; i <= n; ++i) {
                // rnd.wnext(hi, t): in [0, hi-1]
                int p = rnd.wnext(i-1, bias) + 1;
                edges.emplace_back(p, i);
            }
        }
        // shuffle edge order for extra randomness
        shuffle(edges.begin(), edges.end());
    }
    // output
    println(n);
    for (auto &e : edges)
        println(e.first, e.second);
    return 0;
}
