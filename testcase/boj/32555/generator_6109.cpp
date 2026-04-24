#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Password length N and number of guesses M
    int N = rnd.next(2, 10);
    int M = rnd.next(1, 10);

    // Choose a constant number of Y per row (K) with low/medium/high bias
    double p = rnd.next();
    int K;
    if (p < 0.3) {
        K = rnd.next(0, min(2, M));
    } else if (p > 0.7) {
        K = rnd.next(max(0, M - 2), M);
    } else {
        K = rnd.next(0, M);
    }

    // Sigma must be at least 2*N to allow distinct fillers for gray positions
    int sigma_min = 2 * N;
    int sigma_max = min(sigma_min + 10, 100);
    int Sigma = rnd.next(sigma_min, sigma_max);

    // Build the color matrix C with N rows and M columns
    vector<string> C(N, string(M, 'G'));
    for (int i = 0; i < N; i++) {
        // choose K distinct columns to be 'Y' in row i
        vector<int> cols(M);
        iota(cols.begin(), cols.end(), 0);
        shuffle(cols.begin(), cols.end());
        for (int t = 0; t < K; t++) {
            C[i][cols[t]] = 'Y';
        }
    }

    // Output the test case
    println(N, M);
    for (auto &row : C)
        printf("%s\n", row.c_str());
    println(Sigma);

    return 0;
}
