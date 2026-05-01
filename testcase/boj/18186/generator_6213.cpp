#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Size hyperparameter
    int N = rnd.next(3, 15);
    // Cost hyperparameter
    int B = rnd.next(1, 20);
    int rel = rnd.next(0, 2); // 0: C < B, 1: C == B, 2: C > B
    int C;
    if (rel == 0) {
        C = rnd.next(1, min(B, 20));
    } else if (rel == 1) {
        C = B;
    } else {
        C = rnd.next(B, 20);
    }
    // Ai maximum
    int maxAi;
    if (rnd.next(0,1) == 0) {
        maxAi = rnd.next(0, 5);
    } else {
        maxAi = rnd.next(5, 10);
    }
    // Pattern for Ai
    int pattern = rnd.next(0, 3);
    vector<int> A(N);
    if (pattern == 0) {
        // fully random
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(0, maxAi);
    } else if (pattern == 1) {
        // alternating zeros and randoms
        bool zeroOdd = rnd.next(0,1);
        for (int i = 0; i < N; i++) {
            if (((i % 2) == 0) == zeroOdd) A[i] = 0;
            else A[i] = rnd.next(0, maxAi);
        }
    } else if (pattern == 2) {
        // one contiguous zero block
        int zeroLen = rnd.next(1, N - 2);
        int zeroStart = rnd.next(1, N - zeroLen);
        int zeroEnd = zeroStart + zeroLen - 1;
        for (int i = 1; i <= N; i++) {
            if (i >= zeroStart && i <= zeroEnd) A[i-1] = 0;
            else A[i-1] = rnd.next(0, maxAi);
        }
    } else {
        // one peak and others small
        int peakPos = rnd.next(1, N);
        for (int i = 1; i <= N; i++) {
            if (i == peakPos) A[i-1] = maxAi;
            else A[i-1] = rnd.next(0, maxAi);
        }
    }
    // Output
    println(N, B, C);
    println(A);
    return 0;
}
