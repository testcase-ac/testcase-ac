#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(1, 5);
    long long R = 0, G = 0;

    if (type == 1) {
        // co-prime case
        do {
            R = rnd.next(1LL, 1000000000LL);
            G = rnd.next(1LL, 1000000000LL);
        } while (gcd(R, G) != 1);
    } else if (type == 2) {
        // one divides the other
        long long base = rnd.next(1LL, 100000000LL);
        long long k = rnd.next(1LL, 10LL);
        if (rnd.next(0, 1) == 0) {
            R = base;
            G = base * k;
        } else {
            R = base * k;
            G = base;
        }
    } else if (type == 3) {
        // equal numbers
        R = rnd.next(1LL, 1000000000LL);
        G = R;
    } else if (type == 4) {
        // moderate gcd
        long long g = rnd.next(2LL, 100000LL);
        long long a = rnd.next(1LL, 10000LL);
        long long b = rnd.next(1LL, 10000LL);
        R = g * a;
        G = g * b;
    } else {
        // highly composite small numbers with a common factor
        vector<int> primes = {2, 3, 5, 7, 11, 13};
        shuffle(primes.begin(), primes.end());
        long long r = 1, gg = 1;
        for (int i = 0; i < 3; i++) r *= primes[i];
        for (int i = 2; i < 6; i++) gg *= primes[i];
        vector<int> com = {2, 3};
        shuffle(com.begin(), com.end());
        long long c = 1LL * com[0] * com[1];
        R = r * c;
        G = gg * c;
    }

    println(R, G);
    return 0;
}
