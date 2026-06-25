#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long randomBoundedMask(int bits) {
    long long value = 0;
    for (int i = 0; i < bits; ++i) {
        if (rnd.next(2) == 1) {
            value |= (1LL << i);
        }
    }
    return max(1LL, min(value, LIMIT));
}

long long makeCase() {
    int mode = rnd.next(7);

    if (mode == 0) {
        return rnd.next(1, 64);
    }

    if (mode == 1) {
        int bit = rnd.next(0, 59);
        return min(1LL << bit, LIMIT);
    }

    if (mode == 2) {
        int bits = rnd.next(1, 59);
        return (1LL << bits) - 1;
    }

    if (mode == 3) {
        int bit = rnd.next(1, 59);
        long long base = 1LL << bit;
        long long delta = rnd.next(-8, 8);
        return max(1LL, min(base + delta, LIMIT));
    }

    if (mode == 4) {
        long long delta = rnd.next(0LL, 1000000LL);
        return LIMIT - delta;
    }

    if (mode == 5) {
        return randomBoundedMask(rnd.next(1, 60));
    }

    return rnd.next(1LL, LIMIT);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 40);
    vector<long long> cases;
    cases.push_back(1);
    cases.push_back(4);
    cases.push_back(31);
    cases.push_back(1125899906842624LL);
    cases.push_back(LIMIT);

    while ((int)cases.size() < t) {
        cases.push_back(makeCase());
    }

    shuffle(cases.begin(), cases.end());
    println((int)cases.size());
    for (long long value : cases) {
        println(value);
    }

    return 0;
}
