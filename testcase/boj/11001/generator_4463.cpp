#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int D = rnd.next(1, N);

    // Generate a non-increasing temperature sequence T
    vector<long long> T(N);
    // Starting temperature range choice
    int startMax = rnd.any(vector<int>{10, 50, 100});
    T[0] = rnd.next(1LL, (long long)startMax);
    // How likely to stay flat vs drop
    int plateauPct = rnd.next(0, 100);
    // Maximum drop step
    int dropMax = rnd.any(vector<int>{1, 3, 5, 10});
    for (int i = 1; i < N; i++) {
        long long prev = T[i-1];
        // Can only drop if prev > 1
        if (prev > 1 && rnd.next(0, 99) >= plateauPct) {
            long long maxDec = min<long long>(dropMax, prev - 1);
            long long dec = rnd.next(1LL, maxDec);
            T[i] = prev - dec;
        } else {
            T[i] = prev;
        }
    }

    // Generate value sequence V
    vector<long long> V(N);
    int valueMax = rnd.any(vector<int>{10, 50, 100});
    for (int i = 0; i < N; i++) {
        V[i] = rnd.next(1LL, (long long)valueMax);
    }

    // Output
    println(N, D);
    println(T);
    println(V);

    return 0;
}
