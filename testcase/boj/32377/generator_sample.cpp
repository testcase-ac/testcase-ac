#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;

    long long n;
    long long x;
    long long y;
    long long z;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        n = rnd.next(1LL, 30LL);
        x = rnd.next(1LL, 12LL);
        y = rnd.next(1LL, 12LL);
        z = rnd.next(1LL, 12LL);
    } else if (mode == 1) {
        long long base = rnd.next(1LL, 40LL);
        n = rnd.next(1LL, 60LL);
        x = base;
        y = base;
        z = base;
    } else if (mode == 2) {
        long long base = rnd.next(2LL, 100LL);
        n = rnd.next(1LL, 80LL);
        x = base;
        y = base + rnd.next(-1LL, 1LL);
        z = base + rnd.next(-1LL, 1LL);
        x = max(1LL, x);
        y = max(1LL, y);
        z = max(1LL, z);
    } else if (mode == 3) {
        n = rnd.next(1LL, 120LL);
        x = rnd.next(1LL, 8LL);
        y = rnd.next(20LL, 200LL);
        z = rnd.next(20LL, 200LL);
    } else if (mode == 4) {
        n = rnd.next(1LL, 150LL);
        x = rnd.next(2LL, 20LL);
        y = x * rnd.next(2LL, 10LL);
        z = x * rnd.next(2LL, 10LL);
    } else if (mode == 5) {
        n = rnd.next(1LL, 1000000000LL);
        long long base = rnd.next(999999900LL, LIM);
        x = base;
        y = rnd.next(999999900LL, LIM);
        z = rnd.next(999999900LL, LIM);
    } else if (mode == 6) {
        n = rnd.next(1LL, 1000000000LL);
        x = rnd.next(1LL, 5LL);
        y = rnd.next(999999900LL, LIM);
        z = rnd.next(999999900LL, LIM);
    } else {
        n = rnd.next(1LL, 1000000000LL);
        vector<long long> times = {
            rnd.next(1LL, 1000LL),
            rnd.next(1LL, 1000000LL),
            rnd.next(1LL, LIM),
        };
        shuffle(times.begin(), times.end());
        x = times[0];
        y = times[1];
        z = times[2];
    }

    vector<long long> times = {x, y, z};
    if (rnd.next(0, 1)) {
        shuffle(times.begin(), times.end());
        x = times[0];
        y = times[1];
        z = times[2];
    }

    println(n, x, y, z);
    return 0;
}
