#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // Small N for hand-checkable
        int N = rnd.next(1, 10);

        // Hyper-parameter: choose value range
        int lowVal = rnd.next(1, 5);
        int highVal = rnd.next(lowVal, 20);

        // Scenario type: 0=random, 1=sorted, 2=bitonic
        int scenario = rnd.next(0, 2);
        vector<int> a(N);

        if (scenario == 0) {
            // Completely random
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(lowVal, highVal);
            }
        } else if (scenario == 1) {
            // Monotonic: ascending or descending
            for (int i = 0; i < N; ++i) {
                if (N == 1) {
                    a[i] = rnd.next(lowVal, highVal);
                } else {
                    a[i] = lowVal + (highVal - lowVal) * i / (N - 1);
                }
            }
            if (rnd.next(0,1)) {
                reverse(a.begin(), a.end());
            }
        } else {
            // Bitonic: increase then decrease
            int peak = rnd.next(0, N - 1);
            for (int i = 0; i < N; ++i) {
                if (i <= peak) {
                    if (peak == 0) {
                        a[i] = highVal;
                    } else {
                        a[i] = lowVal + (highVal - lowVal) * i / peak;
                    }
                } else {
                    int len = (N - 1) - peak;
                    if (len == 0) {
                        a[i] = highVal;
                    } else {
                        a[i] = lowVal + (highVal - lowVal) * ((N - 1) - i) / len;
                    }
                }
            }
        }

        // Maybe sprinkle a few random swaps for noise
        double swapProb = rnd.next(0.0, 1.0);
        for (int i = 0; i + 1 < N; ++i) {
            if (rnd.next() < swapProb) {
                swap(a[i], a[i+1]);
            }
        }

        // Output this test
        println(N);
        println(a);
    }
    return 0;
}
