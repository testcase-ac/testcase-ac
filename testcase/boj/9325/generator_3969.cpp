#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: 1 to 5
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Base car price s in [1, 100000]
        int s = rnd.next(1, 100000);
        println(s);

        // Decide number of options n with some diversity
        double r = rnd.next();
        int n;
        if (r < 0.3) {
            // no options
            n = 0;
        } else if (r < 0.7) {
            // few options (1..5)
            int hi = rnd.wnext(5, -1) + 1;  // hi in [1..5]
            n = rnd.next(1, hi);
        } else {
            // more options (lo..10) biased high
            int lo = rnd.wnext(10, 1);      // max of 2 samples in [0..9]
            lo = min(max(lo, 1), 10);
            n = rnd.next(lo, 10);
        }
        println(n);

        // Generate each option: quantity q ∈ [1..100], price p ∈ [1..10000]
        for (int i = 0; i < n; ++i) {
            int hiQ = rnd.wnext(100, -1) + 1;    // in [1..100]
            int q   = rnd.next(1, hiQ);
            int hiP = rnd.wnext(10000, -1) + 1;  // in [1..10000]
            int p   = rnd.next(1, hiP);
            println(q, p);
        }
    }

    return 0;
}
