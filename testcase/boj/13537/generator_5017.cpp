#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size hyper-parameter
    int N = rnd.next(1, 10);

    // Value range hyper-parameter
    const int MAXV = 1000000000;
    const int HALFV = 500000000;
    int valSpread = rnd.next(0, 2);
    int loVal, hiVal;
    if (valSpread == 0) {
        // Full range
        loVal = 1;
        hiVal = MAXV;
    } else if (valSpread == 1) {
        // Small values
        loVal = 1;
        hiVal = 100;
    } else {
        // Random subrange of size up to HALFV
        loVal = rnd.next(1, MAXV - HALFV);
        hiVal = rnd.next(loVal, min(MAXV, loVal + HALFV));
    }

    // Generate sequence
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(loVal, hiVal);
    }
    // Sequence shape hyper-parameter
    int seqType = rnd.next(0, 2);
    if (seqType == 1) {
        sort(A.begin(), A.end());
    } else if (seqType == 2) {
        sort(A.begin(), A.end(), greater<int>());
    } // else leave random

    // Compute actual min/max from sequence
    int minA = *min_element(A.begin(), A.end());
    int maxA = *max_element(A.begin(), A.end());

    // Number of queries
    int M = rnd.next(1, 20);

    // Output header
    println(N);
    println(A);
    println(M);

    // Prepare weights for interval length bias
    vector<int> wts = {-2, 0, 2};

    // Generate queries
    for (int qi = 0; qi < M; qi++) {
        // Interval length biased: small, medium, or large
        int t = rnd.any(wts);
        int len = rnd.wnext(N, t) + 1;  // from 1 to N
        if (len > N) len = N;
        int i = rnd.next(1, N - len + 1);
        int j = i + len - 1;

        // k-value hyper-parameter
        int kType = rnd.next(0, 3);
        int k;
        if (kType == 0) {
            // fully random
            k = rnd.next(1, MAXV);
        } else if (kType == 1) {
            // small k
            k = rnd.next(1, min(minA, MAXV));
        } else if (kType == 2) {
            // mid-range k
            k = rnd.next(minA, maxA);
        } else {
            // large k
            k = rnd.next(maxA, MAXV);
        }

        println(i, j, k);
    }

    return 0;
}
