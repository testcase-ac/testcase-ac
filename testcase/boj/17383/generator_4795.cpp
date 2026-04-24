#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter: number of tasks
    int N = rnd.next(1, 10);
    // Hyperparameter: maximum duration value
    int maxVal = rnd.next(5, 20);
    // Choose distribution type: 0 = uniform, 1 = bimodal
    int distType = rnd.next(0, 1);

    vector<int> T(N);
    int smallHi = maxVal / 3;
    int lowLarge = maxVal * 2 / 3;
    for (int i = 0; i < N; i++) {
        if (distType == 0) {
            // Uniform distribution over [1, maxVal]
            T[i] = rnd.next(1, maxVal);
        } else {
            // Bimodal: small or large
            if (rnd.next(0, 1) == 0) {
                // Small durations
                T[i] = rnd.next(1, smallHi);
            } else {
                // Large durations
                T[i] = rnd.next(lowLarge, maxVal);
            }
        }
    }

    // Hyperparameter: whether to sort the durations
    bool doSort = rnd.next(0, 1);
    if (doSort) {
        sort(T.begin(), T.end());
    } else {
        shuffle(T.begin(), T.end());
    }

    // Output
    println(N);
    println(T);
    return 0;
}
