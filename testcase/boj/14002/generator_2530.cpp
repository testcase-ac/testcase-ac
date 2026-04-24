/* generator code */
#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sequence length
    int N = rnd.next(2, 10);

    // Maximum value for elements
    int maxVal = rnd.next(1, 100);

    // Skew parameter for weighted generation (-3 to 3, 0 means uniform)
    int skewT = rnd.next(-3, 3);

    // Generate sequence A
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        if (skewT == 0) {
            // Uniform distribution
            A[i] = rnd.next(1, maxVal);
        } else {
            // Skewed distribution: t>0 biases towards larger, t<0 towards smaller
            A[i] = rnd.wnext(maxVal, skewT);
            // Ensure within [1, maxVal]
            if (A[i] < 1) A[i] = 1;
            if (A[i] > maxVal) A[i] = maxVal;
        }
    }

    // Output
    println(N);
    // Print sequence on one line
    for (int i = 0; i < N; ++i) {
        printf(i ? " %d" : "%d", A[i]);
    }
    printf("\n");

    return 0;
}
