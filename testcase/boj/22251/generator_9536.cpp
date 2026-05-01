#include "testlib.h"
using namespace std;

long long pow10ll(int k) {
    long long r = 1;
    while (k--) r *= 10;
    return r;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, K, P, X;

    int type = rnd.next(0, 9);

    if (type == 0) {
        // Single digit, full range
        K = 1;
        long long maxN = pow10ll(K) - 1; // 9
        N = (int)maxN;
        P = rnd.next(1, 7); // max flips for one digit
        X = rnd.next(1, N);
    } else if (type == 1) {
        // Single digit, smaller N
        K = 1;
        long long maxN = pow10ll(K) - 1; // 9
        N = rnd.next(1, (int)maxN);
        P = rnd.next(1, 7);
        X = rnd.next(1, N);
    } else if (type == 2) {
        // K = 6, N near maximum
        K = 6;
        long long maxN = pow10ll(K) - 1; // 999999
        long long lowN = max(1LL, maxN - 100);
        N = (int)rnd.next((int)lowN, (int)maxN);
        P = rnd.next(1, 42);
        X = rnd.next(1, N);
    } else if (type == 3) {
        // N is exactly 10^K - 1, P=42
        K = rnd.next(2, 6);
        long long maxN = pow10ll(K) - 1;
        N = (int)maxN;
        P = 42;
        X = rnd.next(1, N);
    } else if (type == 4) {
        // Medium K, random N, very small P
        K = rnd.next(2, 6);
        long long maxN = pow10ll(K) - 1;
        N = (int)rnd.next(1, (int)maxN);
        P = rnd.next(1, min(3, 42));
        X = rnd.next(1, N);
    } else if (type == 5) {
        // Random K, mid-range P up to 7*K
        K = rnd.next(1, 6);
        long long maxN = pow10ll(K) - 1;
        N = (int)rnd.next(1, (int)maxN);
        int maxFlips = 7 * K;
        P = rnd.next(1, min(42, maxFlips));
        X = rnd.next(1, N);
    } else if (type == 6) {
        // Edge X = 1
        K = rnd.next(1, 6);
        long long maxN = pow10ll(K) - 1;
        N = (int)rnd.next(1, (int)maxN);
        P = rnd.next(1, 42);
        X = 1;
    } else if (type == 7) {
        // Edge X = N
        K = rnd.next(1, 6);
        long long maxN = pow10ll(K) - 1;
        N = (int)rnd.next(1, (int)maxN);
        P = rnd.next(1, 42);
        X = N;
    } else if (type == 8) {
        // Many leading zeros on X (small X, larger K and N)
        K = rnd.next(2, 6);
        long long maxN = pow10ll(K) - 1;
        long long minN = max(10LL, maxN / 10);
        if (minN > maxN) minN = 1;
        N = (int)rnd.next((int)minN, (int)maxN);
        P = rnd.next(1, 42);
        int upperX = min(N, 100);
        X = rnd.next(1, upperX);
    } else { // type == 9
        // Large K, very small N to emphasize leading zeros
        K = 6;
        long long maxN = pow10ll(K) - 1;
        int upperN = min(1000, (int)maxN);
        N = rnd.next(10, upperN);
        P = rnd.next(1, 42);
        X = rnd.next(1, N);
    }

    println(N, K, P, X);
    return 0;
}
