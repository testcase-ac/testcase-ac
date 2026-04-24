#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size parameters
    int N = rnd.next(1, 10);

    // Bias K towards small or large splits for diversity
    int K;
    if (rnd.next() < 0.5) {
        // bias towards small K
        K = rnd.wnext(N, -1) + 1;
    } else {
        // bias towards large K
        K = rnd.wnext(N, 1) + 1;
    }

    // Hyper-parameters for sequence generation
    int maxBit = rnd.next(0, 29);      // highest bit we may set
    double bitDensity = rnd.next();    // probability to set each bit
    double clusterProb = rnd.next();   // probability to repeat previous value

    // Generate sequence A with optional clustering
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < clusterProb) {
            // repeat previous for clustering
            A[i] = A[i - 1];
        } else {
            int x = 0;
            for (int b = 0; b <= maxBit; b++) {
                if (rnd.next() < bitDensity) {
                    x |= (1 << b);
                }
            }
            A[i] = x;
        }
    }

    // Ensure at least one non-zero to avoid trivial all-zero case
    bool anyNonZero = false;
    for (int x : A) if (x != 0) anyNonZero = true;
    if (!anyNonZero && N > 0) {
        int idx = rnd.next(0, N - 1);
        int b = rnd.next(0, maxBit);
        A[idx] |= (1 << b);
    }

    // Output format
    println(N, K);
    println(A);

    return 0;
}
