#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_N = 1000000000000000000LL;
const long long MOD = 313109LL;

long long evenFromHalf(long long half) {
    half = max(1LL, min(MAX_N / 2, half));
    return half * 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int q = rnd.next(1, mode == 5 ? 80 : 30);
    vector<long long> values;

    auto addHalf = [&](long long half) {
        values.push_back(evenFromHalf(half));
    };

    if (mode == 0) {
        q = rnd.next(1, 12);
        for (int i = 0; i < q; ++i) {
            addHalf(rnd.next(1LL, 40LL));
        }
    } else if (mode == 1) {
        q = rnd.next(6, 24);
        long long start = rnd.next(1LL, 200LL);
        long long step = rnd.next(1LL, 15LL);
        for (int i = 0; i < q; ++i) {
            addHalf(start + i * step);
        }
    } else if (mode == 2) {
        q = rnd.next(8, 30);
        for (int i = 0; i < q; ++i) {
            long long center = rnd.any(vector<long long>{MOD, 2 * MOD, MOD * MOD});
            addHalf(center + rnd.next(-8LL, 8LL));
        }
    } else if (mode == 3) {
        q = rnd.next(8, 30);
        for (int i = 0; i < q; ++i) {
            int exponent = rnd.next(0, 58);
            long long half = 1LL << min(exponent, 58);
            addHalf(half + rnd.next(-3LL, 3LL));
        }
    } else if (mode == 4) {
        q = rnd.next(8, 30);
        for (int i = 0; i < q; ++i) {
            long long half = rnd.next(MAX_N / 2 - 1000000LL, MAX_N / 2);
            addHalf(half);
        }
    } else {
        q = rnd.next(20, 80);
        for (int i = 0; i < q; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) {
                addHalf(rnd.next(1LL, 200LL));
            } else if (bucket == 1) {
                addHalf(MOD + rnd.next(-20LL, 20LL));
            } else if (bucket == 2) {
                addHalf((1LL << rnd.next(10, 58)) + rnd.next(-5LL, 5LL));
            } else if (bucket == 3) {
                addHalf(rnd.next(1LL, 1000000000LL));
            } else {
                addHalf(rnd.next(MAX_N / 2 - 100000LL, MAX_N / 2));
            }
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (long long n : values) {
        println(n);
    }

    return 0;
}
