#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedProduct(int power, int odd) {
    long long value = (1LL << power) * odd;
    if (value > 1000000000LL) {
        value = 1000000000LL;
    }
    return static_cast<int>(value);
}

int randomOdd(int limit) {
    int x = rnd.next(1, limit);
    if (x % 2 == 0) {
        --x;
    }
    return max(1, x);
}

int makeValue(int mode) {
    if (mode == 0) {
        return rnd.next(1, 30);
    }
    if (mode == 1) {
        int power = rnd.next(0, 12);
        int oddLimit = min(999, 1000000000 / (1 << power));
        return boundedProduct(power, randomOdd(oddLimit));
    }
    if (mode == 2) {
        int power = rnd.next(20, 29);
        int oddLimit = max(1, 1000000000 / (1 << power));
        return boundedProduct(power, randomOdd(oddLimit));
    }
    if (mode == 3) {
        int base = rnd.next(999999950, 1000000000);
        return base;
    }

    int small = rnd.next(1, 2000);
    int shift = rnd.next(0, 8);
    long long value = 1LL * small * (1 << shift);
    return static_cast<int>(min(value, 1000000000LL));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 80);
    vector<int> values;
    values.reserve(t);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8, 16, 31, 32, 33,
        999999998, 999999999, 1000000000
    };
    shuffle(anchors.begin(), anchors.end());
    for (int x : anchors) {
        if (static_cast<int>(values.size()) < t) {
            values.push_back(x);
        }
    }

    while (static_cast<int>(values.size()) < t) {
        int mode = rnd.next(0, 4);
        values.push_back(makeValue(mode));
    }

    shuffle(values.begin(), values.end());

    println(t);
    for (int x : values) {
        println(x);
    }

    return 0;
}
