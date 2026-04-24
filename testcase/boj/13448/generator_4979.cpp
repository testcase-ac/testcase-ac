#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of problems
    int N = rnd.next(1, 10);

    // Generate R_i (time), P_i (penalty rate), M_i (base score)
    vector<int> R(N), P(N), M(N);
    for (int i = 0; i < N; i++) {
        // Hyper-parameter for R: small or large
        if (rnd.next(0, 1) == 0)
            R[i] = rnd.next(1, 20);
        else
            R[i] = rnd.next(21, 100);

        // Hyper-parameter for P: small or large
        if (rnd.next(0, 1) == 0)
            P[i] = rnd.next(1, 10);
        else
            P[i] = rnd.next(11, 1000);

        // M_i relative to R_i * P_i, to allow negative or positive net gain
        int maxM = min(100000, R[i] * P[i] * 2);
        if (maxM < 1) maxM = 1;
        M[i] = rnd.next(1, maxM);
    }

    // Total time sum
    long long sumR = 0;
    for (int t : R) sumR += t;

    // Hyper-parameter for total time T
    int T;
    if (rnd.next(0, 2) == 0) {
        // Exactly equals sum of times
        T = (int)sumR;
    } else {
        // Random between 1 and up to 2 * sumR (capped by 100000)
        int hi = min<long long>(100000, sumR * 2 + 1);
        int lo = 1;
        if (hi < lo) hi = lo;
        T = rnd.next(lo, hi);
    }

    // Output in the required format
    println(N, T);
    println(M);
    println(P);
    println(R);

    return 0;
}
