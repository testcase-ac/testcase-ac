#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of trees
    int n = rnd.next(2, 10);
    // Maximum base height
    int maxH = rnd.next(5, 20);
    // Choose a pattern for heights
    int pattern = rnd.next(0, 3);
    vector<int> d(n);
    if (pattern == 0) {
        // Completely random heights
        for (int i = 0; i < n; i++)
            d[i] = rnd.next(1, maxH);
    } else if (pattern == 1) {
        // Mostly increasing
        d[0] = rnd.next(1, maxH);
        for (int i = 1; i < n; i++)
            d[i] = d[i-1] + rnd.next(0, maxH/2 + 1);
    } else if (pattern == 2) {
        // Mostly decreasing
        d[0] = rnd.next(1, maxH);
        for (int i = 1; i < n; i++)
            d[i] = max(1, d[i-1] - rnd.next(0, maxH/2 + 1));
    } else {
        // Random walk
        d[0] = rnd.next(1, maxH);
        vector<int> deltas = {-2, -1, 0, 1, 2};
        for (int i = 1; i < n; i++) {
            int delta = rnd.any(deltas);
            d[i] = max(1, d[i-1] + delta);
        }
    }
    // Number of queries, biased by weighted choice
    int maxQ = min(n-1, 5);
    int t_q = rnd.next(-1, 1);
    int q = rnd.wnext(maxQ, t_q) + 1;
    // Generate each k_i with its own bias
    vector<int> ks(q);
    for (int i = 0; i < q; i++) {
        int t = rnd.next(-2, 2);
        ks[i] = rnd.wnext(n-1, t) + 1;
    }
    // Output
    println(n);
    println(d);
    println(q);
    for (int k : ks) println(k);
    return 0;
}
