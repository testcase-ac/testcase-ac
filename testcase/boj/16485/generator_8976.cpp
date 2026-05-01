#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long c, b;
    int scenario = rnd.next(0, 9); // choose one of 10 patterns

    switch (scenario) {
        case 0: {
            // Both small random
            c = rnd.next(1, 20);
            b = rnd.next(1, 20);
            break;
        }
        case 1: {
            // c is a multiple of b (subtask 1 style)
            long long bCand = rnd.next(1, 1000000000);
            long long maxK = 1000000000LL / bCand;
            long long k = rnd.next(1LL, min(50LL, maxK));
            b = bCand;
            c = bCand * k;
            break;
        }
        case 2: {
            // b is a multiple of c
            long long cCand = rnd.next(1, 1000000000);
            long long maxK = 1000000000LL / cCand;
            long long k = rnd.next(1LL, min(50LL, maxK));
            c = cCand;
            b = cCand * k;
            break;
        }
        case 3: {
            // c and b equal (ratio = 1)
            long long v = rnd.next(1, 1000000000);
            c = v;
            b = v;
            break;
        }
        case 4: {
            // One very large, one small
            if (rnd.next(0, 1) == 0) {
                c = rnd.next(500000000, 1000000000);
                b = rnd.next(1, 100);
            } else {
                c = rnd.next(1, 100);
                b = rnd.next(500000000, 1000000000);
            }
            break;
        }
        case 5: {
            // Both near upper bound
            int lo = 1000000000 - 1000;
            c = rnd.next(lo, 1000000000);
            b = rnd.next(lo, 1000000000);
            break;
        }
        case 6: {
            // One is 1, the other is random large
            if (rnd.next(0, 1) == 0) {
                c = 1;
                b = rnd.next(1, 1000000000);
            } else {
                c = rnd.next(1, 1000000000);
                b = 1;
            }
            break;
        }
        case 7: {
            // Small primes
            vector<int> primes = {
                2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                73, 79, 83, 89, 97
            };
            c = rnd.any(primes);
            b = rnd.any(primes);
            break;
        }
        case 8: {
            // Powers of two
            int e1 = rnd.next(0, 29); // 2^29 < 1e9
            int e2 = rnd.next(0, 29);
            c = 1LL << e1;
            b = 1LL << e2;
            break;
        }
        case 9: {
            // Fully random in [1, 1e9]
            c = rnd.next(1, 1000000000);
            b = rnd.next(1, 1000000000);
            break;
        }
    }

    println(c, b);
    return 0;
}
