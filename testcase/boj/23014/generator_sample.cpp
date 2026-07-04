#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

const long long MAX_VALUE = 1000000000000000000LL;

long long randomValue(int p) {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return rnd.next(1, 1000);
    }
    if (mode == 1) {
        long long value = 1;
        int exponent = rnd.next(1, 8);
        for (int i = 0; i < exponent && value <= MAX_VALUE / p; ++i) {
            value *= p;
        }
        return value;
    }
    if (mode == 2) {
        long long value = 1;
        int exponent = rnd.next(1, 6);
        for (int i = 0; i < exponent && value <= MAX_VALUE / p; ++i) {
            value *= p;
        }
        return min(MAX_VALUE, value + rnd.next(0, 20));
    }
    if (mode == 3) {
        return rnd.next(1LL, 1000000000LL);
    }
    if (mode == 4) {
        return MAX_VALUE - rnd.next(0LL, 1000LL);
    }
    return rnd.next(1LL, MAX_VALUE);
}

int randomS() {
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        return rnd.next(1, 4);
    }
    if (mode == 1) {
        return rnd.next(1, 50);
    }
    if (mode == 2) {
        return rnd.next(100000000, 1000000000);
    }
    return rnd.any(vector<int>{1, 2, 3, 4, 5, 999999937, 1000000000});
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 17, 97, 999999937};
    int t = rnd.next(1, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 12);
        int q = rnd.next(1, 25);
        int p = rnd.any(primes);

        println(n, q, p);

        vector<long long> a(n);
        for (long long& value : a) {
            value = randomValue(p);
        }
        println(a);

        int forcedType2 = rnd.next(1, q);
        for (int queryIndex = 1; queryIndex <= q; ++queryIndex) {
            bool type2 = (queryIndex == forcedType2) || rnd.next(0, 99) < 55;
            if (!type2) {
                int pos = rnd.next(1, n);
                long long value = randomValue(p);
                println(1, pos, value);
            } else {
                int l = rnd.next(1, n);
                int r = rnd.next(l, n);
                println(2, randomS(), l, r);
            }
        }
    }

    return 0;
}
