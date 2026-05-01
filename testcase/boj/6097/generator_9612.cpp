#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long N;
    int P;

    int mode = rnd.next(0, 4); // 5 simple modes

    switch (mode) {
        case 0: {
            // Very small, easy to verify
            N = rnd.next(1, 20);
            P = rnd.next(1, 10);
            break;
        }
        case 1: {
            // Base 1, huge exponent (always "1")
            N = 1;
            P = rnd.next(1, 100000);
            break;
        }
        case 2: {
            // Single-digit base, with a chance for near-limit digit length
            N = rnd.next(2, 9);
            int sub = rnd.next(0, 2);
            if (sub == 0) {
                // tiny exponent
                P = rnd.next(1, 20);
            } else if (sub == 1) {
                // medium exponent
                P = rnd.next(21, 12000);
            } else {
                // large exponent, but still within 15000-digit limit
                // For base 9, digits ~ P * log10(9) + 1 < 0.96 P + 1
                // so P up to 14999 is safe.
                P = rnd.next(13000, 14999);
            }
            break;
        }
        case 3: {
            // Powers of 10 (many trailing zeros)
            int k = rnd.next(1, 4); // 10, 100, 1000, 10000
            long long base = 1;
            for (int i = 0; i < k; ++i) base *= 10;
            N = base;
            // digits(N^P) = 1 + P * k, so ensure <= 15000
            int maxP = (15000 - 1) / k;
            if (maxP < 1) maxP = 1;
            P = rnd.next(1, maxP);
            break;
        }
        case 4: {
            // Larger base, small exponent, keeping result within 15000 digits
            // Sometimes near upper bound, sometimes just random
            if (rnd.next(0, 1) == 0)
                N = rnd.next(1900000000LL, 2000000000LL);
            else
                N = rnd.next(10LL, 2000000000LL);

            // Count decimal digits of N without floating point
            long long temp = N;
            int d = 0;
            while (temp > 0) {
                temp /= 10;
                ++d;
            }
            if (d == 0) d = 1;

            // digits(N^P) <= P * d, require <= 15000
            int maxP = 15000 / d;
            if (maxP < 1) maxP = 1;
            if (maxP > 100000) maxP = 100000; // obey problem constraint on P

            P = rnd.next(1, maxP);
            break;
        }
    }

    println(N, P);
    return 0;
}
