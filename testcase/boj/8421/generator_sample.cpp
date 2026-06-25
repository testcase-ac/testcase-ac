#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000LL;

    long long n = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        long long root = rnd.next(1LL, 1000000LL);
        long long base = root * root;
        long long delta = rnd.next(-50LL, 50LL);
        n = max(1LL, min(LIMIT, base + delta));
    } else if (mode == 2) {
        vector<long long> factors = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        shuffle(factors.begin(), factors.end());
        n = 1;
        for (long long f : factors) {
            while (n <= LIMIT / f && rnd.next(0, 2) != 0) {
                n *= f;
            }
        }
    } else if (mode == 3) {
        long long block = rnd.next(1LL, 1000000LL);
        long long quotient = rnd.next(1LL, 1000000LL);
        n = min(LIMIT, block * quotient + rnd.next(0LL, block - 1));
    } else if (mode == 4) {
        n = LIMIT - rnd.next(0LL, 1000000LL);
    } else {
        n = rnd.next(1LL, LIMIT);
    }

    println(n);
    return 0;
}
