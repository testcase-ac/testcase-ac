#include "testlib.h"
#include <bits/stdc++.h>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    int K = rnd.next(1, 5);
    int P = M * K;

    bool wantStress = rnd.next(0, 1) == 0;
    long long minSum = 1LL * N * (N - 1) / 2;

    vector<int> A;
    if (wantStress && minSum < P) {
        // Impossible case: minimal distinct sum < P, so STRESS
        A.resize(N);
        for (int i = 0; i < N; i++) A[i] = i;
        shuffle(A.begin(), A.end());
    } else {
        // Enough-supply case
        int maxVal = max(N - 1, P) + rnd.next(0, 20);
        vector<int> pool(maxVal + 1);
        iota(pool.begin(), pool.end(), 0);
        shuffle(pool.begin(), pool.end());
        A.assign(pool.begin(), pool.begin() + N);
        long long sum = accumulate(A.begin(), A.end(), 0LL);
        if (sum < P) {
            // increase the largest element to meet requirement
            int idx = max_element(A.begin(), A.end()) - A.begin();
            A[idx] += (P - sum);
        }
        shuffle(A.begin(), A.end());
    }

    // Output
    println(N);
    println(M, K);
    println(A);

    return 0;
}
