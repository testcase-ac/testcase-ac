#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIM = 1000000000000000000LL;

long long randomPowerOfTwo() {
    int exp = rnd.next(0, 59);
    return 1LL << exp;
}

long long randomSmallSigned(long long limit) {
    long long value = rnd.next(0LL, limit);
    if (rnd.next(0, 1)) value = -value;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    long long n = 0;
    long long d = 1;

    if (mode == 0) {
        n = 0;
        d = rnd.next(1, 3) == 1 ? 1 : randomPowerOfTwo();
    } else if (mode == 1) {
        d = randomPowerOfTwo();
        n = randomSmallSigned(min(LIM, d * rnd.next(0LL, 20LL)));
    } else if (mode == 2) {
        d = randomPowerOfTwo();
        n = randomSmallSigned(LIM / d) * d;
    } else if (mode == 3) {
        d = rnd.next(1LL, 1000LL);
        n = randomSmallSigned(1000LL);
    } else if (mode == 4) {
        long long base = rnd.next(1LL, 1000000LL);
        d = base * 3;
        n = randomSmallSigned(1000000000LL);
    } else if (mode == 5) {
        vector<long long> denominators = {1, 2, 3, 4, 5, 8, 16, 31, 64, 1024};
        d = rnd.any(denominators);
        n = rnd.next(-1000000LL, 1000000LL);
    } else if (mode == 6) {
        d = rnd.next(999999999999999900LL, LIM);
        n = rnd.next(-LIM, LIM);
    } else {
        d = rnd.next(1LL, LIM);
        n = rnd.next(-LIM, LIM);
    }

    println(n, d);
    return 0;
}
