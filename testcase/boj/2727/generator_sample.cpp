#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N = 2147483647;

int boundedPower(int base, int maxValue) {
    long long value = 1;
    int exponent = rnd.next(0, 30);
    for (int i = 0; i < exponent && value * base <= maxValue; ++i) {
        value *= base;
    }
    return (int)value;
}

int randomSmoothNumber() {
    long long value = 1;
    int exp2 = rnd.next(0, 30);
    int exp3 = rnd.next(0, 19);

    for (int i = 0; i < exp2 && value * 2 <= MAX_N; ++i) value *= 2;
    for (int i = 0; i < exp3 && value * 3 <= MAX_N; ++i) value *= 3;

    return (int)value;
}

int nearValue(int center) {
    int delta = rnd.next(-25, 25);
    long long value = (long long)center + delta;
    value = max(1LL, min((long long)MAX_N, value));
    return (int)value;
}

int makeCase() {
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        vector<int> edges = {1, 2, 3, 7, 31, MAX_N};
        return rnd.any(edges);
    }
    if (mode == 1) return boundedPower(2, MAX_N);
    if (mode == 2) return boundedPower(3, MAX_N);
    if (mode == 3) return randomSmoothNumber();
    if (mode == 4) return nearValue(boundedPower(2, MAX_N));
    if (mode == 5) return nearValue(boundedPower(3, MAX_N));
    if (mode == 6) return rnd.next(1, 1000000);
    return rnd.next(1, MAX_N);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 80);
    println(t);
    for (int i = 0; i < t; ++i) {
        println(makeCase());
    }

    return 0;
}
