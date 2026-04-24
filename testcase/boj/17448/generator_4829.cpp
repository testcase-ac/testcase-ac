#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of integers
    int N = rnd.next(1, 10);

    // Hyper-parameter: K selection mode (small, large, uniform)
    int mode = rnd.next(0, 2);
    int K;
    if (mode == 0) {
        // small K
        int hi = max(1, N / 2);
        K = rnd.next(1, hi);
    } else if (mode == 1) {
        // large K
        K = rnd.next(N, 2 * N);
    } else {
        // uniform K
        K = rnd.next(1, 2 * N);
    }

    // Hyper-parameter: choose maximum absolute value
    int absMode = rnd.next(1, 3);
    long long maxAbs = (absMode == 1 ? 10 : (absMode == 2 ? 100000LL : 1000000000LL));

    // Hyper-parameters: probability of zero and probability of negative
    double zeroProb = rnd.next(0.0, 0.3);
    double negProb = rnd.next(0.0, 1.0);

    // Generate the array
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next() < zeroProb) {
            a[i] = 0;
        } else {
            a[i] = rnd.next(1LL, maxAbs);
            if (rnd.next() < negProb)
                a[i] = -a[i];
        }
    }

    // Output
    println(N, K);
    println(a);

    return 0;
}
