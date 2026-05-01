#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int K_MAX = 1000000000;
    int N;
    long long K;

    auto genSlopeK = [&](int n) -> long long {
        if (n == 1) {
            return (long long)rnd.next(1, K_MAX);
        }
        long long n2 = 1LL * n * n;
        long long maxT = K_MAX / n2;
        long long minT = max(1LL, (long long)n - 1); // c >= -2
        if (minT > maxT) minT = maxT;
        long long t = rnd.next((int)minT, (int)maxT);
        return t * n2;
    };

    auto genAbsK = [&](int n) -> long long {
        if (n == 1) {
            return (long long)rnd.next(1, K_MAX); // any K works for 1x1
        }
        long long base = 1LL * n * (1LL * n * n - 1) / 3; // sum of |i-j|
        long long n2 = 1LL * n * n;
        long long maxC = (base >= K_MAX) ? 0 : (K_MAX - base) / n2;
        long long c = rnd.next(0, (int)maxC);
        return base + c * n2;
    };

    int mode = rnd.next(0, 6);

    switch (mode) {
        case 0: { // tiny N, small K
            N = rnd.next(1, 3);
            K = rnd.next(1, 30);
            break;
        }
        case 1: { // small N, guaranteed-YES via slope pattern
            N = rnd.next(1, 10);
            K = genSlopeK(N);
            break;
        }
        case 2: { // small N, guaranteed-YES via |i-j| pattern
            N = rnd.next(1, 10);
            K = genAbsK(N);
            break;
        }
        case 3: { // moderate N, mix of YES and random
            N = rnd.next(5, 50);
            if (rnd.next(0, 1) == 0) K = genSlopeK(N);
            else K = rnd.next(1, K_MAX);
            break;
        }
        case 4: { // large N, mostly random with some YES
            N = rnd.next(50, 1000);
            int sub = rnd.next(0, 2);
            if (sub == 0) K = genSlopeK(N);
            else if (sub == 1) K = genAbsK(N);
            else K = rnd.next(1, K_MAX);
            break;
        }
        case 5: { // special crafted edge-like cases
            int sub = rnd.next(0, 3);
            if (sub == 0) { // N = 1, various K
                N = 1;
                vector<long long> cand = {
                    1LL, 2LL, 7LL, 8LL,
                    999999937LL, // large prime-ish
                    (long long)K_MAX
                };
                K = rnd.any(cand);
            } else if (sub == 1) { // N = 2, hand-picked K
                N = 2;
                vector<long long> cand = {
                    1LL, 2LL, 3LL, 4LL, 5LL,
                    8LL, 10LL, 12LL,
                    (long long)K_MAX
                };
                K = rnd.any(cand);
            } else if (sub == 2) { // N = 3, include samples and boundaries
                N = 3;
                vector<long long> cand = {
                    1LL, 2LL, 3LL, 7LL, 8LL, // 7 is sample YES, 1 sample NO
                    18LL, 36LL,             // from slope family (min and base)
                    (long long)K_MAX
                };
                K = rnd.any(cand);
            } else { // N = 1000, guaranteed-YES
                N = 1000;
                if (rnd.next(0, 1) == 0) K = genSlopeK(N);
                else K = genAbsK(N);
            }
            break;
        }
        case 6: default: { // ensure some max-N, extreme K
            N = 1000;
            int sub = rnd.next(0, 2);
            if (sub == 0) {
                K = genSlopeK(N);           // could be very large YES
            } else if (sub == 1) {
                K = genAbsK(N);             // another YES family
            } else {
                // random but skewed toward extremes
                if (rnd.next(0, 1) == 0)
                    K = rnd.next(1, 50);    // very small
                else
                    K = rnd.next(K_MAX - 50, K_MAX); // very large
            }
            break;
        }
    }

    if (K < 1) K = 1;
    if (K > K_MAX) K = K_MAX;

    println(N, K);
    return 0;
}
