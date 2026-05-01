#include "testlib.h"
#include <algorithm>
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Height K and number of games G
    long long K = rnd.next(1LL, 60LL);
    int G = rnd.next(5, 20);

    // Number of leaves
    unsigned long long N = 1ULL << (K - 1);

    println(K, G);

    for (int i = 0; i < G; i++) {
        unsigned long long a, b;
        if (N == 1) {
            // Only one leaf
            a = b = 1;
        } else {
            int t = rnd.next(1, 100);
            if (t <= 15) {
                // Type 1: single leaf
                a = b = rnd.next(1ULL, N);
            } else if (t <= 30) {
                // Type 2: full range
                a = 1;
                b = N;
            } else if (t <= 50) {
                // Type 3: aligned power-of-two interval
                // choose depth d so that number of intervals <= 2^30
                long long minD = max(1LL, K - 30);
                long long maxD = K - 1;
                long long d = rnd.next(minD, maxD);
                unsigned long long len = 1ULL << d;
                unsigned long long cnt = N / len; // <= 2^29
                unsigned long long idx = rnd.next(0ULL, cnt - 1);
                a = idx * len + 1;
                b = a + len - 1;
            } else if (t <= 70) {
                // Type 4: small random interval length <= 3
                unsigned long long maxLen = min(3ULL, N);
                unsigned long long len = rnd.next(1ULL, maxLen);
                a = rnd.next(1ULL, N - len + 1);
                b = a + len - 1;
            } else {
                // Type 5: arbitrary random interval
                a = rnd.next(1ULL, N);
                b = rnd.next(a, N);
            }
        }
        println(a, b);
    }

    return 0;
}
