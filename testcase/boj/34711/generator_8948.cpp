#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXN = 1000000000000LL;
    long long N = 1;

    int mode = rnd.next(0, 5); // choose one of several patterns

    if (mode == 0) {
        // Very small N (edge cases, easy to verify)
        N = rnd.next(1, 15);
    } else if (mode == 1) {
        // Small / medium N
        N = rnd.next(1, 1000);
    } else if (mode == 2) {
        // Completely random in full range
        N = rnd.next(1LL, MAXN);
    } else if (mode == 3) {
        // Large N close to the maximum
        long long diff = rnd.next(0, 1000);
        N = MAXN - diff;
        if (N < 1) N = 1;
    } else if (mode == 4) {
        // Near perfect squares
        int k = rnd.next(1, 1000000); // k^2 <= 1e12
        long long base = 1LL * k * k;
        int deltaType = rnd.next(0, 2); // 0: exact square, 1: -1, 2: +1
        if (deltaType == 1 && base > 1) base--;
        else if (deltaType == 2 && base < MAXN) base++;
        N = base;
    } else if (mode == 5) {
        // Near triangular numbers
        int k = rnd.next(1, 1500000); // roughly sqrt(2*1e12)
        // Adjust k down until k*(k+1)/2 fits in range
        while (true) {
            __int128 tmp = (__int128)k * (k + 1) / 2;
            if (tmp <= MAXN) break;
            --k;
        }
        long long base = (long long)((__int128)k * (k + 1) / 2);
        int deltaType = rnd.next(0, 2); // 0: exact, 1: -1, 2: +1
        if (deltaType == 1 && base > 1) base--;
        else if (deltaType == 2 && base < MAXN) base++;
        N = base;
    }

    println(N);
    return 0;
}
