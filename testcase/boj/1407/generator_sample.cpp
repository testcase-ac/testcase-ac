#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000000000LL;
    int mode = rnd.next(0, 5);
    long long a, b;

    if (mode == 0) {
        a = rnd.next(1LL, 200LL);
        b = rnd.next(a, min(LIM, a + rnd.next(0LL, 80LL)));
    } else if (mode == 1) {
        vector<long long> powers;
        for (long long x = 1; x <= LIM; x *= 2) {
            powers.push_back(x);
        }

        long long center = rnd.any(powers);
        long long leftSlack = min(center - 1, rnd.next(0LL, 30LL));
        long long rightSlack = min(LIM - center, rnd.next(0LL, 30LL));
        a = center - rnd.next(0LL, leftSlack);
        b = center + rnd.next(0LL, rightSlack);
    } else if (mode == 2) {
        long long width = rnd.next(0LL, 1000000LL);
        b = LIM - rnd.next(0LL, 1000000LL);
        a = max(1LL, b - width);
    } else if (mode == 3) {
        long long block = 1LL << rnd.next(1, 49);
        long long quotient = rnd.next(1LL, max(1LL, LIM / block));
        long long center = quotient * block;
        long long radius = rnd.next(0LL, min(block - 1, 100000LL));
        a = max(1LL, center - rnd.next(0LL, radius));
        b = min(LIM, center + rnd.next(0LL, radius));
    } else if (mode == 4) {
        long long aBucket = rnd.next(0LL, 999999LL);
        long long bBucket = rnd.next(aBucket, min(999999LL, aBucket + rnd.next(0LL, 1000LL)));
        a = aBucket * 1000000000LL + rnd.next(1LL, 1000000000LL);
        b = bBucket * 1000000000LL + rnd.next(1LL, 1000000000LL);
        if (a > b) swap(a, b);
    } else {
        a = rnd.next(1LL, LIM);
        long long maxWidth = min(1000000000000LL, LIM - a);
        b = a + rnd.next(0LL, maxWidth);
    }

    println(a, b);
    return 0;
}
