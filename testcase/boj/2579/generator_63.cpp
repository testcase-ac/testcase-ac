#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter 1: choose an upper bound for N, between 5 and 15
    int N_max = rnd.next(5, 15);
    // Number of stairs is then between 1 and N_max
    int N = rnd.next(1, N_max);

    // Hyperparameter 2: choose a maximum possible score, up to 1000
    int maxScore = rnd.next(1, 1000);
    // And a probability bias for “higher” scores
    double highProb = rnd.next(0.0, 1.0);

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < highProb && maxScore >= 2) {
            // draw from the upper half of [1..maxScore]
            int low = maxScore/2 + 1;
            println(rnd.next(low, maxScore));
        } else {
            // draw from the lower half (or full range if maxScore==1)
            int high = maxScore/2 > 0 ? maxScore/2 : maxScore;
            println(rnd.next(1, high));
        }
    }

    return 0;
}
