#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n in small, medium, or slightly larger regimes for variability
    double regime = rnd.next();
    int n;
    if (regime < 0.3) {
        n = rnd.next(2, 5);
    } else if (regime < 0.8) {
        n = rnd.next(6, 10);
    } else {
        n = rnd.next(11, 12);
    }

    // Directed edges maximum
    int maxEdges = n * (n - 1);
    // Sample an upper bound for m skewed towards higher values
    int ub = rnd.wnext(maxEdges - 1, 1) + 1; // ub in [1, maxEdges]
    int m = rnd.next(1, ub);

    // Hyper-parameters for cost distribution
    double smallProb = rnd.next(0.0, 1.0);
    int smallLimit = rnd.any(vector<int>{5, 10, 20});
    int largeLimit = rnd.any(vector<int>{50, 100, 200, 1000});
    if (largeLimit <= smallLimit) {
        largeLimit = smallLimit + rnd.next(1, 100);
    }

    // Output n and m
    println(n);
    println(m);

    // Generate m directed edges (with possible duplicates) with varied costs
    for (int i = 0; i < m; i++) {
        int u = rnd.next(1, n), v = rnd.next(1, n);
        while (u == v) {
            v = rnd.next(1, n);
        }
        int cost;
        if (rnd.next() < smallProb) {
            cost = rnd.next(1, smallLimit);
        } else {
            cost = rnd.next(smallLimit + 1, largeLimit);
        }
        println(u, v, cost);
    }

    return 0;
}
