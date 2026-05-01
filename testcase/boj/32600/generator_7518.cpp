#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of steps
    int n = rnd.next(1, 10);
    // Hyper-parameter for graph density
    double dens = rnd.next(0.0, 1.0);
    int maxEdges = n * (n - 1);
    int upper = max(0, min(maxEdges, (int)round(dens * maxEdges)));
    int m = upper > 0 ? rnd.next(0, upper) : 0;

    // Generate failure probabilities with bias towards extremes and mid
    vector<int> xi(n);
    for (int i = 0; i < n; i++) {
        int t = rnd.next(-1, 1);
        // xi in [0,1000]
        xi[i] = rnd.wnext(1001, t);
    }

    // Build all possible directed edges (no self-loops)
    vector<pair<int,int>> edges;
    edges.reserve(maxEdges);
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= n; b++) {
            if (a != b) edges.emplace_back(a, b);
        }
    }
    shuffle(edges.begin(), edges.end());
    edges.resize(m);

    // Output
    println(n, m);
    // Probabilities with exactly three decimal places
    for (int i = 0; i < n; i++) {
        double p = xi[i] / 1000.0;
        printf("%.3f%c", p, i + 1 == n ? '\n' : ' ');
    }
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
