#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small size N and M
    int N = rnd.next(1, 10);
    long long maxPairs = 1LL * N * (N + 1) / 2;
    int M = rnd.next(1, (int)min(20LL, maxPairs));
    // Value range hyper-parameter
    vector<int> valueLimits;
    valueLimits.push_back(N);
    valueLimits.push_back(10);
    valueLimits.push_back(rnd.next(N, max(100, N)));
    int valueRange = rnd.any(valueLimits);
    // Block probability for runs of equal values
    double blockProb = rnd.next(); // in [0,1)
    // Generate sequence
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < blockProb) {
            A[i] = A[i - 1];
        } else {
            A[i] = rnd.next(1, valueRange);
        }
    }
    // Output N and sequence
    println(N);
    println(A);
    // Generate queries with some special cases
    println(M);
    for (int qi = 0; qi < M; qi++) {
        double r = rnd.next();
        int i, j;
        if (r < 0.2) {
            // single-point query
            i = rnd.next(1, N);
            j = i;
        } else if (r < 0.3) {
            // full range
            i = 1;
            j = N;
        } else {
            // random interval
            i = rnd.next(1, N);
            j = rnd.next(1, N);
            if (i > j) swap(i, j);
        }
        println(i, j);
    }
    return 0;
}
