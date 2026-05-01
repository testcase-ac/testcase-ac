#include "testlib.h"
using namespace std;

long long gcdll(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXV = 2000000000LL;

    long long A = 1, B = 1;
    int type = rnd.next(0, 9);

    switch (type) {
        case 0: { // Root node
            A = 1;
            B = 1;
            break;
        }
        case 1: { // Very small random coprime
            do {
                A = rnd.next(1LL, 20LL);
                B = rnd.next(1LL, 20LL);
            } while (gcdll(A, B) != 1);
            break;
        }
        case 2: { // Small/medium random coprime
            do {
                A = rnd.next(1LL, 1000LL);
                B = rnd.next(1LL, 1000LL);
            } while (gcdll(A, B) != 1);
            break;
        }
        case 3: { // One is 1, the other is large
            long long bigLo = MAXV - 100000000LL;
            if (bigLo < 1) bigLo = 1;
            long long big = rnd.next(bigLo, MAXV);
            if (rnd.next(0, 1) == 0) {
                A = 1;
                B = big;
            } else {
                A = big;
                B = 1;
            }
            break;
        }
        case 4: { // Very skewed: one small (>1), one large
            long long small = rnd.next(2, 10);
            long long bigLo = MAXV - 100000000LL;
            if (bigLo < small + 1) bigLo = small + 1;
            long long big;
            do {
                big = rnd.next(bigLo, MAXV);
            } while (gcdll(small, big) != 1);
            if (rnd.next(0, 1) == 0) {
                A = small;
                B = big;
            } else {
                A = big;
                B = small;
            }
            break;
        }
        case 5: { // Near-equal large consecutive numbers
            long long baseLo = MAXV - 100000000LL;
            if (baseLo < 1) baseLo = 1;
            long long baseHi = MAXV - 1;
            if (baseHi < baseLo) baseHi = baseLo;
            long long base = rnd.next(baseLo, baseHi);
            if (rnd.next(0, 1) == 0) {
                A = base;
                B = base + 1;
            } else {
                A = base + 1;
                B = base;
            }
            break;
        }
        case 6: { // Fibonacci pair
            vector<long long> fib;
            fib.push_back(1);
            fib.push_back(1);
            while (true) {
                long long nxt = fib.back() + fib[(int)fib.size() - 2];
                if (nxt > MAXV) break;
                fib.push_back(nxt);
            }
            if (fib.size() <= 2) {
                A = 1;
                B = 1;
            } else {
                int idx = rnd.next(0, (int)fib.size() - 2);
                long long x = fib[idx];
                long long y = fib[idx + 1];
                if (rnd.next(0, 1) == 0) {
                    A = x;
                    B = y;
                } else {
                    A = y;
                    B = x;
                }
            }
            break;
        }
        case 7: { // From a random path in the tree (moderate depth)
            long long a = 1, b = 1;
            int maxLen = 50;
            int len = rnd.next(1, maxLen);
            for (int i = 0; i < len; i++) {
                bool goLeft = (rnd.next(0, 1) == 0);
                long long na = goLeft ? (a + b) : a;
                long long nb = goLeft ? b : (a + b);
                if (na > MAXV || nb > MAXV) break;
                a = na;
                b = nb;
            }
            A = a;
            B = b;
            break;
        }
        case 8: { // Fully random coprime in full range
            do {
                A = rnd.next(1LL, MAXV);
                B = rnd.next(1LL, MAXV);
            } while (gcdll(A, B) != 1);
            break;
        }
        case 9: { // Borderline near maximum values
            int k = rnd.next(0, 3);
            if (k == 0) {
                A = MAXV;
                B = MAXV - 1;
            } else if (k == 1) {
                A = MAXV - 1;
                B = MAXV;
            } else if (k == 2) {
                A = MAXV;
                B = 1;
            } else {
                A = 1;
                B = MAXV;
            }
            break;
        }
    }

    println(A, B);
    return 0;
}
