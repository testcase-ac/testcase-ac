#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: whether to force a large GCD to test formatting
    bool needLargeGcd = rnd.next(0, 1) == 1;

    // Sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // List of small primes for common factors
    vector<int> primes = {
         2,  3,  5,  7, 11, 13, 17, 19, 
        23, 29, 31, 37, 41, 43, 47,
        53, 59, 61, 67, 71, 73, 79,
        83, 89, 97
    };

    // Determine how many common prime factors
    int C;
    if (needLargeGcd) {
        // enough small primes so product likely >1e9
        C = rnd.next(10, 20);
    } else {
        C = rnd.next(0, 5);
    }

    // Initialize factor slots
    vector<long long> A(N, 1), B(M, 1);

    // Assign common primes
    for (int i = 0; i < C; i++) {
        int p = rnd.any(primes);
        // assign to A
        bool doneA = false;
        for (int t = 0; t < 20 && !doneA; t++) {
            int idx = rnd.next(0, N-1);
            if (A[idx] * p <= 1000000000LL) {
                A[idx] *= p;
                doneA = true;
            }
        }
        // assign to B
        bool doneB = false;
        for (int t = 0; t < 20 && !doneB; t++) {
            int idx = rnd.next(0, M-1);
            if (B[idx] * p <= 1000000000LL) {
                B[idx] *= p;
                doneB = true;
            }
        }
        // If both fails, we skip this prime (rare)
    }

    // Add some unique random factors to A
    int UA = rnd.next(0, 5);
    for (int i = 0; i < UA; i++) {
        bool done = false;
        for (int t = 0; t < 20 && !done; t++) {
            int x = rnd.next(1, 10000);
            int idx = rnd.next(0, N-1);
            if (A[idx] * x <= 1000000000LL) {
                A[idx] *= x;
                done = true;
            }
        }
    }

    // Add some unique random factors to B
    int UB = rnd.next(0, 5);
    for (int i = 0; i < UB; i++) {
        bool done = false;
        for (int t = 0; t < 20 && !done; t++) {
            int x = rnd.next(1, 10000);
            int idx = rnd.next(0, M-1);
            if (B[idx] * x <= 1000000000LL) {
                B[idx] *= x;
                done = true;
            }
        }
    }

    // Shuffle the orders to add randomness
    shuffle(A.begin(), A.end());
    shuffle(B.begin(), B.end());

    // Output in correct format
    println(N);
    println(A);
    println(M);
    println(B);

    return 0;
}
