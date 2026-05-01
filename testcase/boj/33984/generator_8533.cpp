#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_A = 1000000;
    int testType = rnd.next(0, 7);

    int N;
    vector<int> A;

    switch (testType) {
        case 0: {
            // Very small indices, small N
            N = rnd.next(1, 10);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                A[i] = rnd.next(1, 10);
            }
            break;
        }
        case 1: {
            // Mix of very small and very large indices
            N = rnd.next(10, 40);
            A.resize(N);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 1) == 0) {
                    A[i] = rnd.next(1, 30); // small
                } else {
                    A[i] = rnd.next(500000, MAX_A); // large
                }
            }
            break;
        }
        case 2: {
            // Strictly increasing sequence with small step
            N = rnd.next(5, 40);
            A.resize(N);
            int start = rnd.next(1, 1000);
            int step = rnd.next(1, 10);
            for (int i = 0; i < N; ++i) {
                A[i] = start + i * step;
            }
            break;
        }
        case 3: {
            // Strictly decreasing sequence with small step
            N = rnd.next(5, 40);
            A.resize(N);
            int base = rnd.next(1, 1000);
            int step = rnd.next(1, 10);
            int start = base + step * (N - 1);
            for (int i = 0; i < N; ++i) {
                A[i] = start - i * step;
            }
            break;
        }
        case 4: {
            // All equal indices, sometimes very large
            N = rnd.next(1, 50);
            A.resize(N);
            int k;
            if (rnd.next(0, 1) == 0) {
                k = rnd.next(1, 20);
            } else {
                k = rnd.next(MAX_A - 100, MAX_A);
            }
            for (int i = 0; i < N; ++i) {
                A[i] = k;
            }
            break;
        }
        case 5: {
            // Alternating small and big indices
            N = rnd.next(2, 50);
            A.resize(N);
            int bigBase = rnd.next(500000, MAX_A);
            vector<int> smallVals = {1, 2, 3, 4, 5};
            for (int i = 0; i < N; ++i) {
                if (i % 2 == 0) {
                    A[i] = rnd.any(smallVals);
                } else {
                    int offset = rnd.next(-3, 3);
                    int val = bigBase + offset;
                    if (val < 1) val = 1;
                    if (val > MAX_A) val = MAX_A;
                    A[i] = val;
                }
            }
            break;
        }
        case 6: {
            // Piecewise segments: constant small/big and short increasing runs
            N = rnd.next(5, 50);
            A.clear();
            int pos = 0;
            while (pos < N) {
                int remain = N - pos;
                int len = rnd.next(1, min(5, remain));
                int pattern = rnd.next(0, 2); // 0: constant small, 1: constant big, 2: increasing
                if (pattern == 0) {
                    int val = rnd.next(1, 20);
                    for (int i = 0; i < len; ++i) A.push_back(val);
                } else if (pattern == 1) {
                    int val = rnd.next(800000, MAX_A);
                    for (int i = 0; i < len; ++i) A.push_back(val);
                } else {
                    int start = rnd.next(1, 1000);
                    for (int i = 0; i < len; ++i) A.push_back(start + i);
                }
                pos += len;
            }
            break;
        }
        case 7: {
            // Many adjacent indices m and m+1, with occasional very small indices
            N = rnd.next(5, 50);
            A.resize(N);
            int m;
            if (rnd.next(0, 1) == 0) {
                // Near the beginning of Fibonacci indices
                m = rnd.next(1, 5);
            } else {
                m = rnd.next(10, MAX_A - 1);
            }
            for (int i = 0; i < N; ++i) {
                int choice = rnd.next(0, 4);
                if (choice == 0) {
                    A[i] = 1;
                } else if (choice == 1) {
                    A[i] = 2;
                } else if (choice == 2) {
                    A[i] = m;
                } else {
                    A[i] = m + 1;
                }
            }
            break;
        }
    }

    println(N);
    println(A);

    return 0;
}
