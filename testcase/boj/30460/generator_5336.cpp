#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of seconds
    int N = rnd.next(3, 10);
    vector<int> A(N);

    // Hyper-parameters for diversity
    int mode = rnd.next(0, 3);
    int maxMag = rnd.any(vector<int>{1, 5, 10, 100, 1000});
    double pZero = rnd.next(0.0, 0.3);
    double pNeg  = rnd.next(0.0, 0.5);

    if (mode == 0) {
        // Fully random with zeros and negative probability
        for (int i = 0; i < N; ++i) {
            if (rnd.next() < pZero) {
                A[i] = 0;
            } else {
                int v = rnd.next(1, maxMag);
                if (rnd.next() < pNeg) v = -v;
                A[i] = v;
            }
        }
    } else if (mode == 1) {
        // Non-decreasing sequence
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(-maxMag, maxMag);
        }
        sort(A.begin(), A.end());
    } else if (mode == 2) {
        // Non-increasing sequence
        for (int i = 0; i < N; ++i) {
            A[i] = rnd.next(-maxMag, maxMag);
        }
        sort(A.begin(), A.end(), greater<int>());
    } else {
        // Wave pattern: even positions >= 0, odd positions <= 0
        for (int i = 0; i < N; ++i) {
            if (i % 2 == 0) {
                if (rnd.next() < pZero) {
                    A[i] = 0;
                } else {
                    A[i] = rnd.next(1, maxMag);
                }
            } else {
                if (rnd.next() < pZero) {
                    A[i] = 0;
                } else {
                    A[i] = -rnd.next(1, maxMag);
                }
            }
        }
    }

    // Output
    println(N);
    println(A);

    return 0;
}
