#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pattern = rnd.next(1, 9);
    int N = 0, K = 0;
    vector<long long> A, B;

    if (pattern == 1) {
        // Very small edge cases
        int sub = rnd.next(0, 3);
        if (sub == 0) {
            N = 1; K = 0;
        } else if (sub == 1) {
            N = 1; K = 2;
        } else if (sub == 2) {
            N = 2; K = rnd.next(0, 4);
        } else {
            N = 2; K = 4;
        }
        A.resize(N);
        B.resize(N);
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 20);
            B[i] = rnd.next(1, 20);
        }
    } else if (pattern == 2) {
        // K = 0, medium N, random arrays
        N = rnd.next(5, 10);
        K = 0;
        A.resize(N);
        B.resize(N);
        long long sumA = 0;
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 20);
            sumA += A[i];
        }
        // Sometimes make B have same sum as A, sometimes different
        if (rnd.next(0, 1) == 0) {
            // Same sum but different distribution
            B = A;
            shuffle(B.begin(), B.end());
        } else {
            long long sumB = 0;
            for (int i = 0; i < N; ++i) {
                B[i] = rnd.next(1, 20);
                sumB += B[i];
            }
            // With small probability, force equal sum by adjusting last element
            if (rnd.next(0, 3) == 0) {
                long long diff = sumA - sumB;
                long long cand = B[N - 1] + diff;
                if (cand >= 1 && cand <= 1000000000LL) {
                    B[N - 1] = cand;
                }
            }
        }
    } else if (pattern == 3) {
        // Max operations K = 2N
        N = rnd.next(5, 15);
        K = 2 * N;
        A.resize(N);
        B.resize(N);
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 50);
            B[i] = rnd.next(1, 50);
        }
    } else if (pattern == 4) {
        // Identical backpacks
        N = rnd.next(3, 10);
        K = rnd.next(0, 2 * N);
        A.resize(N);
        B.resize(N);
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 30);
        }
        B = A;
        // Sometimes slightly tweak one element to break equality
        if (rnd.next(0, 2) == 0) {
            int pos = rnd.next(0, N - 1);
            long long delta = rnd.next(1, 5);
            if (rnd.next(0, 1) == 0) {
                if (B[pos] + delta <= 1000000000LL) B[pos] += delta;
            } else {
                if (B[pos] - delta >= 1) B[pos] -= delta;
            }
        }
    } else if (pattern == 5) {
        // Monotone sequences, possibly opposite directions
        N = rnd.next(4, 12);
        K = rnd.next(0, 2 * N);
        A.resize(N);
        B.resize(N);
        // A increasing or decreasing
        bool incA = rnd.next(0, 1);
        long long baseA = rnd.next(1, 5);
        long long stepA = rnd.next(0, 5);
        for (int i = 0; i < N; ++i) {
            if (incA)
                A[i] = baseA + stepA * i;
            else
                A[i] = baseA + stepA * (N - 1 - i);
            if (A[i] < 1) A[i] = 1;
        }
        // B possibly reverse of A or own monotone
        if (rnd.next(0, 1) == 0) {
            B = A;
            reverse(B.begin(), B.end());
        } else {
            bool incB = rnd.next(0, 1);
            long long baseB = rnd.next(1, 5);
            long long stepB = rnd.next(0, 5);
            for (int i = 0; i < N; ++i) {
                if (incB)
                    B[i] = baseB + stepB * i;
                else
                    B[i] = baseB + stepB * (N - 1 - i);
                if (B[i] < 1) B[i] = 1;
            }
        }
    } else if (pattern == 6) {
        // One backpack much heavier than the other
        N = rnd.next(3, 10);
        K = rnd.next(0, 2 * N);
        A.resize(N);
        B.resize(N);
        bool heavyA = rnd.next(0, 1);
        for (int i = 0; i < N; ++i) {
            if (heavyA) {
                A[i] = rnd.next(30, 100);
                B[i] = rnd.next(1, 5);
            } else {
                A[i] = rnd.next(1, 5);
                B[i] = rnd.next(30, 100);
            }
        }
    } else if (pattern == 7) {
        // Large values near 1e9
        N = rnd.next(5, 10);
        K = rnd.next(0, 2 * N);
        A.resize(N);
        B.resize(N);
        for (int i = 0; i < N; ++i) {
            // Mix huge and small values
            if (rnd.next(0, 1) == 0)
                A[i] = rnd.next(1, 1000);
            else
                A[i] = rnd.next(900000000, 1000000000);
            if (rnd.next(0, 1) == 0)
                B[i] = rnd.next(1, 1000);
            else
                B[i] = rnd.next(900000000, 1000000000);
        }
    } else if (pattern == 8) {
        // Hand-crafted tricky small tests
        int which = rnd.next(0, 3);
        if (which == 0) {
            // Sample from statement
            N = 3; K = 2;
            A = {3, 1, 4};
            B = {1, 5, 9};
        } else if (which == 1) {
            // Symmetric heavy ends
            N = 4; K = 2;
            A = {10, 1, 1, 1};
            B = {1, 1, 1, 10};
        } else if (which == 2) {
            // Needs popping from both sides to optimize
            N = 5; K = 4;
            A = {5, 1, 100, 1, 5};
            B = {1, 50, 1, 50, 1};
        } else {
            N = 6; K = 5;
            A = {20, 1, 1, 50, 1, 1};
            B = {1, 40, 1, 1, 40, 1};
        }
    } else if (pattern == 9) {
        // Correlated arrays: B is shuffled / reversed / slightly tweaked A
        N = rnd.next(5, 15);
        K = rnd.next(0, 2 * N);
        A.resize(N);
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(1, 40);
        }
        B = A;
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            reverse(B.begin(), B.end());
        } else if (mode == 1) {
            shuffle(B.begin(), B.end());
        } else {
            // tweak a few positions
            int changes = rnd.next(1, max(1, N / 2));
            for (int c = 0; c < changes; ++c) {
                int pos = rnd.next(0, N - 1);
                long long delta = rnd.next(1, 10);
                if (rnd.next(0, 1) == 0) {
                    if (B[pos] + delta <= 1000000000LL) B[pos] += delta;
                } else {
                    if (B[pos] - delta >= 1) B[pos] -= delta;
                }
            }
        }
    }

    // Final safety: ensure constraints
    if (K < 0) K = 0;
    if (K > 2 * N) K = 2 * N;
    for (int i = 0; i < (int)A.size(); ++i) {
        if (A[i] < 1) A[i] = 1;
        if (A[i] > 1000000000LL) A[i] = 1000000000LL;
    }
    for (int i = 0; i < (int)B.size(); ++i) {
        if (B[i] < 1) B[i] = 1;
        if (B[i] > 1000000000LL) B[i] = 1000000000LL;
    }

    println(N, K);
    println(A);
    println(B);

    return 0;
}
