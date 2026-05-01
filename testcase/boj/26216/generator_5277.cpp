#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int K = rnd.next(1, 4);
    int H = rnd.next(1, 4);

    // Compute total blue nodes M = (K+1)^H - 1, but keep M <= 20
    auto computeM = [&](int h) {
        long long m = 1;
        for (int i = 0; i < h; i++) m *= (K + 1);
        return m - 1;
    };
    long long M = computeM(H);
    while (H > 1 && M > 20) {
        H--;
        M = computeM(H);
    }
    if (M > 20) {
        H = 1;
        M = computeM(H);
    }

    // Allow some queries to reference non-existent keys
    int extra = rnd.next(0, 3);
    long long key_max = M + extra;

    // Number of queries Q, weighted for diversity
    int t = rnd.next(-2, 2);
    int Q = rnd.wnext(10, t);
    Q = max(1, min(Q, 10));

    // Output
    println(K, H, Q);
    for (int i = 0; i < Q; i++) {
        long long A = rnd.next(1LL, key_max);
        long long B = rnd.next(1LL, key_max);
        if (A > B) swap(A, B);
        println(A, B);
    }
    return 0;
}
