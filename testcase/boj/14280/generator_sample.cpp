#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000LL;

long long clampValue(long long x) {
    return max(1LL, min(LIMIT, x));
}

long long nearValue(long long center, long long radius) {
    return clampValue(center + rnd.next(-radius, radius));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    long long a, b, c;

    if (mode == 0) {
        a = rnd.next(1, 2000);
        b = rnd.next(1, 2000);
        c = a * b;
    } else if (mode == 1) {
        a = rnd.next(1, 5000);
        b = rnd.next(1, 5000);
        c = clampValue(a * b + rnd.next(-2000, 2000));
    } else if (mode == 2) {
        long long baseA = rnd.next(1, 100000);
        long long baseB = rnd.next(1LL, LIMIT / baseA);
        a = nearValue(baseA, 30);
        b = nearValue(baseB, 30);
        c = clampValue(baseA * baseB + rnd.next(-1000, 1000));
    } else if (mode == 3) {
        a = rnd.next(1, 100);
        b = rnd.next(10000000LL, LIMIT);
        c = clampValue(a * b + rnd.next(-100000, 100000));
    } else if (mode == 4) {
        a = rnd.next(10000000LL, LIMIT);
        b = rnd.next(1, 100);
        c = clampValue(a * b + rnd.next(-100000, 100000));
    } else if (mode == 5) {
        a = rnd.next(LIMIT - 1000000, LIMIT);
        b = rnd.next(LIMIT - 1000000, LIMIT);
        c = rnd.next(LIMIT - 1000000, LIMIT);
    } else if (mode == 6) {
        a = rnd.next(1, 50);
        b = rnd.next(1, 50);
        c = rnd.next(1, 50);
    } else {
        vector<long long> values = {1, 2, 3, 10, 999, 1000, 999999937LL, LIMIT};
        a = rnd.any(values);
        b = rnd.any(values);
        c = rnd.any(values);
    }

    println(a, b, c);
    return 0;
}
