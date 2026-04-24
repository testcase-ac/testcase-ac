#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for variability
    int n = rnd.next(1, 15);                // number of elements
    int m = rnd.next(1, 2 * n + 5);         // number of operations
    double findProb = rnd.next(0.0, 1.0);   // probability of a find operation
    double sameProb = rnd.next(0.0, 1.0);   // probability that a == b

    // Output n and m
    println(n, m);

    // Generate operations
    for (int i = 0; i < m; i++) {
        int a = rnd.next(0, n);
        int b = (rnd.next() < sameProb ? a : rnd.next(0, n));
        int tp = (rnd.next() < findProb ? 1 : 0);
        println(tp, a, b);
    }

    return 0;
}
