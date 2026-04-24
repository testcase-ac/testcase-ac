#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length
    int n = rnd.next(1, 10);

    // Decide if negatives and/or positives should appear
    bool incNeg = rnd.next(0, 1);
    bool incPos = rnd.next(0, 1);
    if (!incNeg && !incPos) {
        // ensure at least one side
        if (rnd.next(0, 1)) incNeg = true;
        else incPos = true;
    }

    // Choose lower and upper bounds
    int lower, upper;
    if (incNeg && incPos) {
        lower = -rnd.next(0, 100);
        if (lower >= 0) lower = -rnd.next(1, 100);
        upper = rnd.next(0, 100);
        if (upper <= 0) upper = rnd.next(1, 100);
    } else if (incNeg) {
        lower = -rnd.next(1, 100);
        upper = -1;
    } else {
        lower = 1;
        upper = rnd.next(1, 100);
    }

    // Prepare sequence
    vector<long long> A(n);
    int distType = rnd.next(0, 2);
    vector<long long> extremes = {lower, upper};

    for (int i = 0; i < n; ++i) {
        if (distType == 0) {
            // Uniform
            A[i] = rnd.next(lower, upper);
        } else if (distType == 1) {
            // Only extremes
            A[i] = rnd.any(extremes);
        } else {
            // Mix of uniform and extremes
            if (rnd.next() < 0.5) 
                A[i] = rnd.next(lower, upper);
            else
                A[i] = rnd.any(extremes);
        }
        // Sprinkle zeros if possible
        if (lower <= 0 && upper >= 0 && rnd.next() < 0.2) {
            A[i] = 0;
        }
    }

    // Shuffle to avoid ordering patterns
    shuffle(A.begin(), A.end());

    // Output
    println(n);
    println(A);

    return 0;
}
