#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long randomNear(long long center, long long radius) {
    long long lo = max(1LL, center - radius);
    long long hi = min(LIMIT, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = rnd.next(8, 30);
    vector<long long> values;

    if (mode == 0) {
        t = rnd.next(8, 20);
        for (int i = 0; i < t; ++i) values.push_back(rnd.next(1LL, 20LL));
    } else if (mode == 1) {
        t = rnd.next(10, 25);
        for (int i = 0; i < t; ++i) values.push_back(rnd.next(1LL, 5000LL));
    } else if (mode == 2) {
        t = rnd.next(12, 30);
        long long start = rnd.next(1LL, 200000LL);
        for (int i = 0; i < t; ++i) values.push_back(min(LIMIT, start + i));
    } else if (mode == 3) {
        t = rnd.next(8, 18);
        for (int i = 0; i < t; ++i) {
            long long base = rnd.next(1LL, 1000000000LL);
            values.push_back(base * base);
        }
    } else if (mode == 4) {
        t = rnd.next(8, 20);
        for (int i = 0; i < t; ++i) values.push_back(randomNear(LIMIT, 1000000LL));
    } else {
        t = rnd.next(10, 24);
        for (int i = 0; i < t; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                values.push_back(rnd.next(1LL, 100LL));
            } else if (bucket == 1) {
                values.push_back(rnd.next(101LL, 5000LL));
            } else if (bucket == 2) {
                values.push_back(rnd.next(5001LL, 1000000000000LL));
            } else {
                values.push_back(randomNear(LIMIT, 1000000000000LL));
            }
        }
    }

    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);
    values.push_back(5000);
    values.push_back(LIMIT);
    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (long long value : values) println(value);

    return 0;
}
