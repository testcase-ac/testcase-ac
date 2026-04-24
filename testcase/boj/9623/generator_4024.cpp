#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Small sequence length
        int N = rnd.next(1, 10);
        // Maximum absolute value for elements
        int M = rnd.next(1, 10);
        // Probability for zeros and positives
        double zeroProb = rnd.next(0.0, 0.3);
        double posProb = rnd.next(0.0, 1.0);

        // Generate the array
        vector<int> a(N);
        for (int i = 0; i < N; i++) {
            double r = rnd.next();
            if (r < zeroProb) {
                a[i] = 0;
            } else if (r < zeroProb + (1 - zeroProb) * posProb) {
                a[i] = rnd.next(1, M);
            } else {
                a[i] = rnd.next(-M, -1);
            }
        }

        // Hyper-parameter for threshold selection
        int mode = rnd.next(0, 3);
        int X;
        int maxSum = M * N;
        int halfSum = (M * N) / 2;
        switch (mode) {
            case 0:
                // Easy: small positive threshold
                X = rnd.next(1, M);
                break;
            case 1:
                // Negative threshold
                X = rnd.next(-M, -1);
                break;
            case 2:
                // Medium-high threshold
                X = rnd.next(halfSum, maxSum);
                break;
            default:
                // Fully random threshold
                X = rnd.next(-maxSum, maxSum);
                break;
        }

        // Output this test case
        println(N, X);
        println(a);
    }

    return 0;
}
