#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_VALUE = 1000000000000000000LL;

long long randomPowerProduct() {
    long long value = 1;
    int twos = rnd.next(0, 18);
    int fives = rnd.next(0, 18);
    for (int i = 0; i < twos && value <= MAX_VALUE / 2; ++i) value *= 2;
    for (int i = 0; i < fives && value <= MAX_VALUE / 5; ++i) value *= 5;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);

        long long a = 1;
        long long b = 1;
        long long pos = 1;
        int n = 1;

        if (mode == 0) {
            a = rnd.next(1LL, 30LL);
            b = rnd.next(1LL, 30LL);
            pos = rnd.next(1LL, 40LL);
            n = rnd.next(1, 30);
        } else if (mode == 1) {
            b = randomPowerProduct();
            a = rnd.next(1LL, min(MAX_VALUE, b * rnd.next(1LL, 20LL)));
            pos = rnd.next(1LL, 80LL);
            n = rnd.next(1, 40);
        } else if (mode == 2) {
            vector<long long> denominators = {3, 6, 7, 9, 11, 13, 27, 37, 81, 101, 9901};
            b = rnd.any(denominators);
            a = rnd.next(1LL, b * rnd.next(1LL, 50LL));
            pos = rnd.next(1LL, 200LL);
            n = rnd.next(1, 60);
        } else if (mode == 3) {
            a = rnd.next(MAX_VALUE - 1000000LL, MAX_VALUE);
            b = rnd.next(MAX_VALUE - 1000000LL, MAX_VALUE);
            pos = rnd.next(MAX_VALUE - 1000000LL, MAX_VALUE);
            n = rnd.next(1, 100);
        } else if (mode == 4) {
            b = rnd.next(1LL, 1000000LL);
            a = rnd.next(MAX_VALUE / 2, MAX_VALUE);
            pos = rnd.next(1LL, MAX_VALUE);
            n = rnd.next(80, 100);
        } else {
            b = 1;
            a = rnd.next(1LL, MAX_VALUE);
            pos = rnd.next(1LL, MAX_VALUE);
            n = rnd.next(1, 100);
        }

        println(a, b);
        println(pos, n);
    }

    return 0;
}
