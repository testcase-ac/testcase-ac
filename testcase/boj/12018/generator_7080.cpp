#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of courses
    int n = rnd.wnext(10, rnd.next(-1,1)) + 1; // 1 to 11 roughly, but cap later
    n = min(n, 10);
    // Total mileage
    int m = rnd.wnext(100, rnd.next(-1,1)) + 1; // 1..100 biased
    // Output header
    println(n, m);
    for (int i = 0; i < n; i++) {
        // categorize course
        int cat = rnd.next(0, 2); // 0: under-subscribed, 1: exact, 2: over-subscribed
        int P, L;
        if (cat == 0) {
            // under: P < L
            P = rnd.next(1, 5);
            L = rnd.next(P+1, min(10, P+5));
        } else if (cat == 1) {
            // exact: P == L
            P = rnd.next(1, 5);
            L = P;
        } else {
            // over: P > L
            P = rnd.next(2, 10);
            L = rnd.next(1, P-1);
        }
        // generate bids
        vector<int> bids(P);
        if (P < L) {
            // random bids anywhere
            for (int j = 0; j < P; j++)
                bids[j] = rnd.next(1, 36);
        } else {
            // create a sharper cutoff: top L bids high, others low
            // sometimes all equal or clustered
            double r = rnd.next();
            if (r < 0.2) {
                // all same
                int x = rnd.next(1, 36);
                for (int j = 0; j < P; j++) bids[j] = x;
            } else {
                int cutoff = L;
                for (int j = 0; j < P; j++) {
                    if (j < cutoff)
                        bids[j] = rnd.next(30, 36);
                    else
                        bids[j] = rnd.next(1, 25);
                }
            }
        }
        // shuffle bids so order is random
        shuffle(bids.begin(), bids.end());
        // output course
        println(P, L);
        println(bids);
    }
    return 0;
}
