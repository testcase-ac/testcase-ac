#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 15);
    println(T);
    vector<long long> baseSmall = {1, 2, 3, 4, 6, 12};
    vector<long long> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    vector<long long> primePowers = {4, 8, 9, 16, 25, 27, 32, 49, 64, 81, 121, 125};
    vector<long long> largePrimes = {
        1000000007LL, 1000000009LL, 1000000033LL, 1000000087LL,
        1000000123LL, 1000000181LL, 1000000207LL, 1000000223LL
    };
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 6);
        long long N;
        switch (type) {
            case 0:
                N = rnd.any(baseSmall);
                break;
            case 1:
                N = rnd.any(smallPrimes);
                break;
            case 2:
                N = rnd.any(primePowers);
                break;
            case 3: {
                long long p = rnd.any(smallPrimes), q;
                do { q = rnd.any(smallPrimes); } while (q == p);
                N = p * q;
            } break;
            case 4:
                N = rnd.any(largePrimes);
                break;
            case 5: {
                long long p = rnd.any(largePrimes), q = rnd.any(smallPrimes);
                __int128 prod = (__int128)p * q;
                if (prod <= (long long)1000000000000000000LL) N = (long long)prod;
                else N = p;
            } break;
            case 6:
                N = rnd.next(1000000000000LL, 1000000000000000000LL);
                break;
        }
        println(N);
    }
    return 0;
}
