#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static const long long LIMIT = 1000000000000000000LL;

long long eightNumber(int digits) {
    long long value = 0;
    for (int i = 0; i < digits; ++i) {
        value = value * 10 + 8;
    }
    return value;
}

long long randomEightNumber(int maxDigits) {
    return eightNumber(rnd.next(1, maxDigits));
}

long long randomLuckyCandidate() {
    int terms = rnd.next(1, 8);
    long long sum = 0;
    for (int i = 0; i < terms; ++i) {
        int maxDigits = 1;
        while (maxDigits < 18 && sum + eightNumber(maxDigits + 1) <= LIMIT) {
            ++maxDigits;
        }
        long long add = randomEightNumber(maxDigits);
        if (sum + add > LIMIT) {
            add = 8;
        }
        sum += add;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> values = {
        1,
        8,
        16,
        64,
        72,
        76,
        88,
        96,
        1000000000000000000LL,
        888888888888888888LL,
    };

    int extra = rnd.next(18, 42);
    for (int i = 0; i < extra; ++i) {
        int mode = rnd.next(0, 5);
        long long value;
        if (mode == 0) {
            value = rnd.next(1LL, 120LL);
        } else if (mode == 1) {
            value = randomLuckyCandidate();
        } else if (mode == 2) {
            long long base = randomLuckyCandidate();
            int delta = rnd.next(-12, 12);
            value = max(1LL, min(LIMIT, base + delta));
        } else if (mode == 3) {
            int digits = rnd.next(1, 18);
            long long base = eightNumber(digits);
            int delta = rnd.next(-40, 40);
            value = max(1LL, min(LIMIT, base + delta));
        } else if (mode == 4) {
            int digits = rnd.next(16, 18);
            long long lo = digits == 18 ? 100000000000000000LL : eightNumber(digits - 1);
            long long hi = min(LIMIT, lo * 10 - 1);
            value = rnd.next(lo, hi);
        } else {
            long long block = eightNumber(rnd.next(1, 17));
            int multiplier = rnd.next(1, 8);
            value = min(LIMIT, block * multiplier + rnd.next(0LL, 80LL));
        }
        values.push_back(value);
    }

    shuffle(values.begin(), values.end());

    println(static_cast<int>(values.size()));
    for (long long value : values) {
        println(value);
    }
    return 0;
}
