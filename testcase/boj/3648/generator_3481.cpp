#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);

    for (int tc = 0; tc < T; ++tc) {
        // Number of participants: small for hand checking
        int n = rnd.next(2, 10);
        // Bias for including contestant 1 in a vote
        double p1Bias = (n <= 2 ? 1.0 : rnd.next(0.0, 1.0));
        // Max number of judges
        int maxM = n * 3;
        // Bias for m distribution
        int mbias = rnd.next(-1, 1);
        int m0 = rnd.wnext(maxM, mbias);
        int m = m0 + 1;  // ensure at least one judge

        // Output this test case
        println(n, m);

        for (int i = 0; i < m; ++i) {
            int u, v;
            // Decide if this vote involves contestant 1
            if (rnd.next() < p1Bias) {
                u = 1;
                // pick another distinct participant
                if (n > 1)
                    v = rnd.next(2, n);
                else
                    v = 1;
            } else {
                if (n <= 2) {
                    // fallback to always include 1 when n=2
                    u = 1; v = 2;
                } else {
                    u = rnd.next(2, n);
                    do { v = rnd.next(2, n); } while (v == u);
                }
            }

            // Choose vote sign pattern: 0=++, 1=--, 2=+-, 3=-+
            int sbias = rnd.next(-1, 1);
            int mode = rnd.wnext(4, sbias);
            int a, b;
            switch (mode) {
                case 0: a = u;  b = v;  break;
                case 1: a = -u; b = -v; break;
                case 2: a = u;  b = -v; break;
                default: a = -u; b = v;  break;
            }

            println(a, b);
        }
    }

    return 0;
}
