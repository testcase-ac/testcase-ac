#include "testlib.h"
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of plates: small and hand-checkable
    int N = rnd.next(1, 10);
    println(N);

    // Probability of generating a "nice" plate
    double niceProb = rnd.next();

    // Hyper-parameter to bias letter codes towards low/mid/high
    int tL = rnd.next(-2, 2);

    for (int i = 0; i < N; ++i) {
        bool isNice = rnd.next() < niceProb;
        int L;
        if (isNice) {
            // letter value in [0..10099] to ensure a D within ±100 stays in [0..9999]
            L = rnd.wnext(10099 + 1, tL);
        } else {
            // full range [0..17575]
            L = rnd.wnext(26*26*26, tL);
        }

        // compute letters from L in base-26
        int x = L;
        char c0 = char('A' + x / (26*26));
        x %= (26*26);
        char c1 = char('A' + x / 26);
        x %= 26;
        char c2 = char('A' + x);

        int D;
        if (isNice) {
            // choose D so that |L - D| <= 100, clipped to [0..9999]
            int lo = L - 100; if (lo < 0) lo = 0;
            int hi = L + 100; if (hi > 9999) hi = 9999;
            D = rnd.next(lo, hi);
        } else {
            // choose D so that |L - D| > 100, clipped to [0..9999]
            bool canLow = (L - 101 >= 0);
            bool canHigh = (L + 101 <= 9999);
            if (canLow && canHigh) {
                // pick one side randomly
                if (rnd.next(0, 1) == 0) {
                    int hi = L - 101;
                    if (hi > 9999) hi = 9999;
                    D = rnd.next(0, hi);
                } else {
                    int lo = L + 101;
                    if (lo < 0) lo = 0;
                    D = rnd.next(lo, 9999);
                }
            } else if (canLow) {
                int hi = L - 101;
                if (hi > 9999) hi = 9999;
                D = rnd.next(0, hi);
            } else {
                int lo = L + 101;
                if (lo < 0) lo = 0;
                D = rnd.next(lo, 9999);
            }
        }

        // output in format LLL-DDDD
        // %04d ensures leading zeros for the numeric part
        printf("%c%c%c-%04d\n", c0, c1, c2, D);
    }

    return 0;
}
