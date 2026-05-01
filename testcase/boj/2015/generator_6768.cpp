#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: bias N towards small or large
    bool biasHigh = rnd.next(0, 1);
    int N;
    if (biasHigh) N = rnd.wnext(30, 2);
    else          N = rnd.wnext(30, -2);
    N = max(N, 1);

    // Choose a pattern for A to expose different cases
    int pattern = rnd.next(0, 3);
    vector<long long> A(N);

    if (pattern == 0) {
        // Fully random with some zeros
        vector<double> zeroProbs = {0.0, 0.1, 0.3, 0.7, 1.0};
        double p0 = zeroProbs[rnd.next(0, (int)zeroProbs.size() - 1)];
        vector<int> maxChoices = {10, 100, 1000};
        int maxV = rnd.any(maxChoices);
        for (int i = 0; i < N; i++) {
            if (rnd.next() < p0) A[i] = 0;
            else                 A[i] = rnd.next(-maxV, maxV);
        }
    } else if (pattern == 1) {
        // Monotonically increasing sequence
        A[0] = rnd.next(-10, 10);
        for (int i = 1; i < N; i++) {
            A[i] = A[i-1] + rnd.next(0, 5);
        }
    } else if (pattern == 2) {
        // Monotonically decreasing sequence
        A[0] = rnd.next(-10, 10);
        for (int i = 1; i < N; i++) {
            A[i] = A[i-1] - rnd.next(0, 5);
        }
    } else {
        // Few constant blocks
        int B = rnd.next(1, min(N, 5));
        int rem = N;
        int idx = 0;
        while (idx < N) {
            int block = rnd.next(1, rem - (B - 1));
            int val = rnd.next(-20, 20);
            for (int j = 0; j < block && idx < N; j++) {
                A[idx++] = val;
            }
            rem -= block;
            B--;
        }
    }

    // Choose K, sometimes forcing K=0, else within possible sum range
    long long K;
    if (rnd.next() < 0.3) {
        K = 0;
    } else {
        long long maxSum = 0;
        for (auto x : A) maxSum += (x >= 0 ? x : -x);
        if (maxSum == 0) {
            K = 0;
        } else {
            K = rnd.next(-maxSum, maxSum);
        }
    }

    // Output
    println(N, K);
    println(A);

    return 0;
}
