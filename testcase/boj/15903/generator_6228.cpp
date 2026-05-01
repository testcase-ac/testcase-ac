#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of cards n between small and medium for hand verification
    int n = rnd.next(2, 20);

    // Hyper-parameter for m: bias towards small, medium, or large by weighted sampling
    vector<int> bias = {-2, -1, 0, 1, 2};
    int t = rnd.any(bias);
    // rnd.wnext(hi, t) picks min or max of |t|+1 samples to bias
    int m = rnd.wnext(15 * n + 1, t);
    // rnd.wnext with hi=15*n+1 gives range [0,15*n]

    // Generate diverse distributions of card values
    vector<int> a(n);
    int distType = rnd.next(0, 2);
    if (distType == 0) {
        // Uniform random across full range
        for (int i = 0; i < n; i++) {
            a[i] = rnd.next(1, 1000000);
        }
    } else if (distType == 1) {
        // Many duplicates: one base value repeated sometimes, rest random
        int base = rnd.next(1, 100);
        for (int i = 0; i < n; i++) {
            if (rnd.next(0, n - 1) == 0)
                a[i] = base;
            else
                a[i] = rnd.next(1, 1000000);
        }
    } else {
        // Two very large cards, others relatively small
        int p1 = rnd.next(0, n - 1);
        int p2;
        do {
            p2 = rnd.next(0, n - 1);
        } while (p2 == p1);
        for (int i = 0; i < n; i++) {
            if (i == p1 || i == p2)
                a[i] = rnd.next(1000000 - 1000, 1000000);
            else
                a[i] = rnd.next(1, 1000);
        }
    }

    // Output in required format
    println(n, m);
    println(a);

    return 0;
}
