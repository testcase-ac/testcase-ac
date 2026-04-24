#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // small sizes for hand-checking
        int n = rnd.next(1, 10);
        int m = rnd.next(1, 20);
        println(n, m);
        vector<int> qs(m);
        // Three modes for diversity
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            // purely random queries
            for (int i = 0; i < m; i++) {
                qs[i] = rnd.next(1, n);
            }
        } else if (mode == 1) {
            // cyclic pattern
            for (int i = 0; i < m; i++) {
                qs[i] = (i % n) + 1;
            }
        } else {
            // heavy repeats of a favored DVD
            int fav = rnd.next(1, n);
            double p = rnd.next() * 0.8 + 0.1; // between 0.1 and 0.9
            for (int i = 0; i < m; i++) {
                if (rnd.next() < p) qs[i] = fav;
                else qs[i] = rnd.next(1, n);
            }
        }
        // Output the queries
        println(qs);
    }
    return 0;
}
