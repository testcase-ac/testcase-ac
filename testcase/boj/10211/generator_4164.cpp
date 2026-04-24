#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: 1 to 10
    int T = rnd.next(1, 10);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        // Array size: 1 to 10
        int N = rnd.next(1, 10);
        println(N);
        // Value range type: 0 = small abs values [-10,10], 1 = full abs range [-999,999]
        int valRange = rnd.next(0, 1);
        int low  = (valRange == 0 ? -10  : -999);
        int high = (valRange == 0 ?  10  :  999);
        // Distribution pattern type
        // 0 = uniform mix, 1 = mostly positive, 2 = mostly negative
        // 3 = alternating sign, 4 = one big positive spike, 5 = all zeros
        int type = rnd.next(0, 5);
        vector<int> X(N, 0);
        if (type == 5) {
            // all zeros
            // X is already zeroed
        }
        else if (type == 4) {
            // one big positive spike, others small
            // small values in [-10,10] clipped to [low,high]
            int smallLow  = max(low,  -10);
            int smallHigh = min(high,  10);
            for (int i = 0; i < N; i++) {
                X[i] = rnd.next(smallLow, smallHigh);
            }
            int j = rnd.next(0, N - 1);
            int spikeLow = max(1, high / 2);
            if (spikeLow > high) spikeLow = high;
            X[j] = rnd.next(spikeLow, high);
        }
        else {
            // other patterns
            for (int i = 0; i < N; i++) {
                double p = rnd.next();
                if (type == 0) {
                    // uniform mix
                    X[i] = rnd.next(low, high);
                }
                else if (type == 1) {
                    // mostly positive
                    if (p < 0.7) {
                        X[i] = rnd.next(max(0, low), high);
                    } else if (p < 0.85) {
                        X[i] = rnd.next(low, min(0, high));
                    } else {
                        X[i] = 0;
                    }
                }
                else if (type == 2) {
                    // mostly negative
                    if (p < 0.7) {
                        X[i] = rnd.next(low, min(0, high));
                    } else if (p < 0.85) {
                        X[i] = rnd.next(max(0, low), high);
                    } else {
                        X[i] = 0;
                    }
                }
                else if (type == 3) {
                    // alternating sign
                    if (i % 2 == 0) {
                        // non-negative
                        X[i] = rnd.next(0, high);
                    } else {
                        // non-positive
                        X[i] = rnd.next(low, 0);
                    }
                }
            }
        }
        // Output the array
        println(X);
    }
    return 0;
}
