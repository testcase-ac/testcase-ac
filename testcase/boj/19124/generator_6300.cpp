#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose n in various ranges
    int p = rnd.next(0, 99);
    long long n;
    if (p < 20) {
        // very small n
        n = rnd.next(1LL, 10LL);
    } else if (p < 40) {
        // small n
        n = rnd.next(11LL, 1000LL);
    } else if (p < 60) {
        // medium n
        n = rnd.next(1001LL, 1000000LL);
    } else if (p < 80) {
        // large n up to 1e12
        n = rnd.next(1000001LL, 1000000000000LL);
    } else {
        // very large n up to 1e18
        n = rnd.next(1000000000001LL, 1000000000000000000LL);
    }
    // Hyper-parameter: choose k among edge cases and random
    long long k;
    int t = rnd.next(0, 4);
    switch (t) {
        case 0:
            k = 0;
            break;
        case 1:
            k = n;
            break;
        case 2:
            k = (n >= 1 ? 1 : 0);
            break;
        case 3:
            k = (n >= 1 ? n - 1 : 0);
            break;
        default:
            k = rnd.next(0LL, n);
            break;
    }
    println(n, k);
    return 0;
}
