#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 7);
    vector<int> A;
    int N = 0;

    // Some helper value sets
    vector<int> smallPrimes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
    vector<int> smallComposites = {
        4,6,8,9,10,12,14,15,16,18,20,21,22,24,25,26,27,28,
        30,32,33,34,35,36,38,39,40,42,44,45,46,48,49,50,51,
        52,54,55,56,57,58,60
    };
    vector<int> oddComposites = {9,15,21,25,27,33,35,39,45,49};

    switch (type) {
        // Type 0: very small N, random mix of small primes/composites
        case 0: {
            N = rnd.next(2, 10);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                int p = rnd.next(0, 99);
                if (p < 30) {
                    // very small numbers 1..5
                    A[i] = rnd.next(1, 5);
                } else if (p < 60) {
                    // small primes
                    A[i] = rnd.any(smallPrimes);
                } else {
                    // small composites
                    A[i] = rnd.any(smallComposites);
                }
            }
            break;
        }

        // Type 1: many ones
        case 1: {
            N = rnd.next(3, 12);
            A.assign(N, 1);
            int ones = rnd.next(2, N); // ensure at least two ones overall
            // First 'ones' stay 1, rest become random 2..30
            for (int i = ones; i < N; ++i) {
                int p = rnd.next(0, 99);
                if (p < 50) {
                    A[i] = rnd.any(smallPrimes);
                } else {
                    A[i] = rnd.any(smallComposites);
                }
            }
            shuffle(A.begin(), A.end());
            break;
        }

        // Type 2: all even composites
        case 2: {
            N = rnd.next(2, 15);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                int k = rnd.next(2, 100); // 2*k >= 4, always composite
                A[i] = 2 * k;
            }
            break;
        }

        // Type 3: all odd, at most one '1'
        case 3: {
            N = rnd.next(2, 15);
            A.resize(N);
            int ones = rnd.next(0, 1); // 0 or 1
            int posOne = -1;
            if (ones == 1) posOne = rnd.next(0, N - 1);
            for (int i = 0; i < N; ++i) {
                if (i == posOne) {
                    A[i] = 1;
                } else {
                    A[i] = rnd.any(oddComposites);
                }
            }
            break;
        }

        // Type 4: arithmetic progression, small step
        case 4: {
            N = rnd.next(5, 20);
            int start = rnd.next(1, 20);
            int diff = rnd.next(1, 7);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                A[i] = start + i * diff;
                // With small probability, bump by 1 to add irregularity
                if (rnd.next(0, 99) < 20 && A[i] + 1 <= 1000000)
                    A[i] += 1;
            }
            break;
        }

        // Type 5: mixture of small and large numbers
        case 5: {
            N = rnd.next(5, 20);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                int p = rnd.next(0, 99);
                if (p < 60) {
                    // small numbers
                    int q = rnd.next(0, 99);
                    if (q < 40) {
                        A[i] = rnd.any(smallPrimes);
                    } else if (q < 80) {
                        A[i] = rnd.any(smallComposites);
                    } else {
                        A[i] = rnd.next(1, 50);
                    }
                } else {
                    // large near 1e6
                    int delta = rnd.next(0, 1000);
                    A[i] = 1000000 - delta;
                }
            }
            break;
        }

        // Type 6: hand-crafted examples (including statement samples)
        case 6: {
            vector<vector<int>> examples = {
                {1, 1},
                {1, 1, 1},
                {1, 2},
                {1, 2, 3},
                {1, 8, 9},
                {2, 3, 4, 5, 6},
                {1, 4, 7, 10},
                {3, 1, 4, 1, 5, 9},
                {30, 41, 66, 70, 104, 110, 153, 165, 231, 385},
                {2520, 2521, 2522, 2523, 2524, 2525}
            };
            A = rnd.any(examples);
            N = (int)A.size();
            break;
        }

        // Type 7: medium N, roughly balanced parity, random values
        case 7: {
            N = rnd.next(8, 25);
            A.resize(N);
            int targetOdd = N / 2;
            int targetEven = N - targetOdd;
            int curOdd = 0, curEven = 0;

            for (int i = 0; i < N; ++i) {
                bool makeOdd;
                if (curOdd == targetOdd) makeOdd = false;
                else if (curEven == targetEven) makeOdd = true;
                else makeOdd = rnd.next(0, 1) == 1;

                if (makeOdd) {
                    ++curOdd;
                    int p = rnd.next(0, 99);
                    if (p < 40) A[i] = rnd.any(oddComposites);
                    else if (p < 70) A[i] = rnd.any(smallPrimes) | 1; // ensure odd
                    else A[i] = rnd.next(1, 59) | 1;
                } else {
                    ++curEven;
                    int p = rnd.next(0, 99);
                    if (p < 40) A[i] = rnd.any(smallComposites);
                    else if (p < 70) {
                        int v = rnd.any(smallPrimes);
                        if (v % 2 == 1) ++v;
                        A[i] = v;
                    } else {
                        int v = rnd.next(2, 60);
                        if (v % 2 == 1) ++v;
                        A[i] = v;
                    }
                }
            }
            break;
        }
    }

    println(N);
    println(A);

    return 0;
}
