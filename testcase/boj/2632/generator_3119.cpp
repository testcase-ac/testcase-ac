#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of slices for A and B
    int m = rnd.next(3, 10);
    int n = rnd.next(3, 10);

    // hyper-parameter: bias towards small or large slices
    bool biasSmall = rnd.next(0, 1);
    int sliceMaxA, sliceMaxB;
    if (biasSmall) {
        // bias towards smaller values
        sliceMaxA = rnd.wnext(1000, -2) + 1;
        sliceMaxB = rnd.wnext(1000, -2) + 1;
    } else {
        // bias towards larger values
        sliceMaxA = rnd.wnext(1000, 2) + 1;
        sliceMaxB = rnd.wnext(1000, 2) + 1;
    }

    // generate slice sizes
    vector<int> A(m), B(n);
    for (int i = 0; i < m; i++) A[i] = rnd.next(1, sliceMaxA);
    for (int i = 0; i < n; i++) B[i] = rnd.next(1, sliceMaxB);

    // random reversal for extra diversity
    if (rnd.next(0,1)) reverse(A.begin(), A.end());
    if (rnd.next(0,1)) reverse(B.begin(), B.end());

    // compute all circular contiguous sums for A
    vector<int> preA(2*m+1, 0);
    for (int i = 1; i <= 2*m; i++)
        preA[i] = preA[i-1] + A[(i-1) % m];
    vector<int> sumsA;
    for (int len = 1; len < m; len++) {
        for (int i = 0; i < m; i++) {
            sumsA.push_back(preA[i+len] - preA[i]);
        }
    }
    // full circle
    int fullA = preA[m];
    sumsA.push_back(fullA);

    // compute all circular contiguous sums for B
    vector<int> preB(2*n+1, 0);
    for (int i = 1; i <= 2*n; i++)
        preB[i] = preB[i-1] + B[(i-1) % n];
    vector<int> sumsB;
    for (int len = 1; len < n; len++) {
        for (int i = 0; i < n; i++) {
            sumsB.push_back(preB[i+len] - preB[i]);
        }
    }
    int fullB = preB[n];
    sumsB.push_back(fullB);

    // choose scenario for K
    // 0: only A, 1: only B, 2: mix, 3: no solution (too large)
    int scen = rnd.next(0, 3);
    int K;
    if (scen == 0) {
        K = rnd.any(sumsA);
    } else if (scen == 1) {
        K = rnd.any(sumsB);
    } else if (scen == 2) {
        K = rnd.any(sumsA) + rnd.any(sumsB);
    } else {
        K = fullA + fullB + rnd.next(1, 10);
    }

    // output
    println(K);
    println(m, n);
    for (int x : A) println(x);
    for (int x : B) println(x);

    return 0;
}
