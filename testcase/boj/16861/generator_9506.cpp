#include "testlib.h"
using namespace std;

bool isHarshad(long long x) {
    long long s = 0, t = x;
    while (t > 0) {
        s += t % 10;
        t /= 10;
    }
    if (s == 0) return false;
    return (x % s == 0);
}

long long nextHarshad(long long x) {
    for (long long n = x; ; ++n) {
        if (isHarshad(n)) return n;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long n;
    int type = rnd.next(0, 9);

    switch (type) {
        case 0: {
            // Smallest possible
            n = 1;
            break;
        }
        case 1: {
            // Largest possible
            n = 1000000000LL;
            break;
        }
        case 2: {
            // Near upper bound
            n = rnd.next(1000000000LL - 1000, 1000000000LL);
            break;
        }
        case 3: {
            // Small random
            n = rnd.next(1, 1000);
            break;
        }
        case 4: {
            // All nines: 9, 99, ..., 999999999
            int len = rnd.next(1, 9);
            long long p = 1;
            for (int i = 0; i < len; ++i) p *= 10;
            n = p - 1;
            break;
        }
        case 5: {
            // Powers of 10: 1, 10, 100, ..., 1e9
            int len = rnd.next(0, 9);
            long long p = 1;
            for (int i = 0; i < len; ++i) p *= 10;
            n = p;
            break;
        }
        case 6: {
            // Random number that is already Harshad
            long long base = rnd.next(1LL, 1000000000LL);
            n = nextHarshad(base);
            break;
        }
        case 7: {
            // Just before a Harshad number
            long long base = rnd.next(2LL, 1000000000LL);
            long long h = nextHarshad(base);
            if (h > 1) n = h - 1;
            else n = 1; // Fallback, though h >= base >= 2 should always hold
            break;
        }
        case 8: {
            // Hand-picked interesting examples
            vector<long long> special = {
                24,        // Harshad
                25,        // Just after Harshad
                156,       // Harshad
                157,       // Non-Harshad
                987654321, // Sample and interesting pattern
                999999999  // Large all-nines Harshad
            };
            n = rnd.any(special);
            break;
        }
        case 9: {
            // Numbers with many zeros and a couple of non-zero digits
            int len = rnd.next(2, 9);
            int lead = rnd.next(1, 9);
            int otherPos = rnd.next(1, len - 1); // position of second non-zero
            int otherDigit = rnd.next(1, 9);

            vector<int> digits(len, 0);
            digits[0] = lead;
            digits[otherPos] = otherDigit;

            long long val = 0;
            for (int d : digits) {
                val = val * 10 + d;
            }
            if (val < 1) val = 1;
            if (val > 1000000000LL) val = 1000000000LL;
            n = val;
            break;
        }
    }

    println(n);
    return 0;
}
