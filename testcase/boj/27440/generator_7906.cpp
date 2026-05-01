#include "testlib.h"
using namespace std;
using ull = unsigned long long;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int tc = rnd.next(0, 7);
    ull N = 1;
    const ull LIM = 1000000000000000000ULL;
    switch (tc) {
        case 0: { // small random
            N = rnd.next(1LL, 10LL);
            break;
        }
        case 1: { // medium random
            N = rnd.next(100000LL, 1000000000LL);
            break;
        }
        case 2: { // large random
            N = rnd.next(1000000000000LL, (long long)LIM);
            break;
        }
        case 3: { // power of two
            int k = rnd.next(0, 59);
            N = (1ULL << k);
            break;
        }
        case 4: { // power of three
            int k = rnd.next(0, 37);
            __int128 t = 1;
            for (int i = 0; i < k; i++) t *= 3;
            N = (ull)t;
            break;
        }
        case 5: { // product 2^a * 3^b
            __int128 t;
            int a, b;
            do {
                a = rnd.wnext(60, -1);
                b = rnd.wnext(38, -1);
                t = (__int128(1) << a);
                for (int i = 0; i < b; i++) t *= 3;
            } while (t < 1 || t > LIM);
            N = (ull)t;
            break;
        }
        case 6: { // power +/- 1
            if (rnd.next(0,1) == 0) {
                int k = rnd.next(0, 59);
                N = (1ULL << k) + 1;
            } else {
                int k = rnd.next(0, 37);
                __int128 t = 1;
                for (int i = 0; i < k; i++) t *= 3;
                N = (ull)(t + 1);
            }
            if (N > LIM) N = LIM;
            break;
        }
        case 7: { // extremes
            if (rnd.next(0,1) == 0) N = 1;
            else N = LIM;
            break;
        }
    }
    println(N);
    return 0;
}
