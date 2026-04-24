#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: sequence length
    int N = rnd.next(2, 10);

    // Hyper-parameter: value bound (ensure at least 1)
    int valueBound = rnd.wnext(100, 2);
    if (valueBound < 1) valueBound = 1;

    // Hyper-parameters for generation
    int maxStep = rnd.next(1, valueBound);
    double incProb = rnd.next(0.0, 1.0);    // probability to continue increasing
    double dupProb = rnd.next(0.0, 1.0);    // probability to duplicate a previous value

    // Compute range for random resets
    int minAi = -rnd.next(0, valueBound);
    int maxAi = rnd.next(0, valueBound);

    vector<long long> A;
    A.reserve(N);

    // Generate sequence with increasing segments, resets, and duplicates
    for (int i = 0; i < N; ++i) {
        long long x;
        if (i > 0 && rnd.next() < dupProb) {
            // duplicate a previous element
            x = rnd.any(A);
        } else if (i > 0 && rnd.next() < incProb) {
            // continue an increasing segment
            long long prev = A.back();
            x = prev + rnd.next(1, maxStep);
        } else {
            // random reset within the range
            x = rnd.next(minAi, maxAi);
        }
        A.push_back(x);
    }

    // Output input for LIS problem
    println(N);
    println(A);

    return 0;
}
