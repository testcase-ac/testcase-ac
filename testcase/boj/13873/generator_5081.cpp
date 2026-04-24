#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter 1: number of nights N
    int N = rnd.next(1, 10);

    // Hyper-parameter 2: decide if K is small (<=N) or large (>N)
    bool smallK = rnd.next(0, 1) == 0;
    int K;
    if (smallK) {
        // Can get free nights
        K = rnd.next(1, N);
    } else {
        // Hard or impossible to get many free nights
        int up = N + rnd.next(1, 10);
        K = min(up, 100000);
    }

    // Hyper-parameter 3: choose maximum price
    vector<int> maxPOpts = {10, 100, 1000, 10000};
    int maxP = rnd.any(maxPOpts);

    // Hyper-parameter 4: distribution type for prices
    int distType = rnd.next(0, 2); // 0=random, 1=ascending, 2=descending

    // Generate prices
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        P[i] = rnd.next(1, maxP);
    }
    if (distType == 1) {
        sort(P.begin(), P.end());
    } else if (distType == 2) {
        sort(P.begin(), P.end(), greater<int>());
    }
    // Occasionally inject a single high spike if random chance
    if (rnd.next(0.0, 1.0) < 0.2) {
        int idx = rnd.next(0, N-1);
        P[idx] = rnd.next(maxP/2 + 1, maxP);
    }

    // Output the generated test
    println(N, K);
    println(P);

    return 0;
}
