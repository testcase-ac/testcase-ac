#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const long long MAX_N = 1000000000000000LL;

long long pow10(int exp) {
    long long value = 1;
    while (exp--) value *= 10;
    return value;
}

long long fromDigits(const string& digits) {
    long long value = 0;
    for (char digit : digits) value = value * 10 + (digit - '0');
    return value;
}

long long randomNumberWithDigits(int length) {
    string digits;
    digits += char('1' + rnd.next(9));
    for (int i = 1; i < length; ++i) digits += char('0' + rnd.next(10));
    return fromDigits(digits);
}

long long cascadeNumber() {
    int length = rnd.next(2, 15);
    string digits(length, '0');
    digits[0] = char('1' + rnd.next(9));

    int suffixLength = rnd.next(1, length - 1);
    int suffixStart = length - suffixLength;
    for (int i = 1; i < suffixStart; ++i) {
        digits[i] = char('0' + rnd.next(10));
    }

    digits[suffixStart] = char('5' + rnd.next(5));
    for (int i = suffixStart + 1; i < length; ++i) {
        digits[i] = rnd.next(2) ? '4' : char('0' + rnd.next(4));
    }

    return fromDigits(digits);
}

long long nearPowerOfTen() {
    int exp = rnd.next(1, 15);
    long long base = pow10(exp);
    long long deltaLimit = min(base - 1, 10000LL);
    long long delta = rnd.next(0LL, deltaLimit);
    if (rnd.next(2) == 0) return max(1LL, base - delta);
    return min(MAX_N, base + delta);
}

long long stableNumber() {
    int length = rnd.next(1, 15);
    string digits(length, '0');
    digits[0] = char('1' + rnd.next(4));
    for (int i = 1; i < length; ++i) {
        digits[i] = char('0' + rnd.next(5));
    }
    return fromDigits(digits);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> fixed = {
        1LL,
        4LL,
        5LL,
        9LL,
        44LL,
        45LL,
        49LL,
        454LL,
        4445LL,
        999999999999999LL,
        MAX_N,
    };

    long long n;
    int mode = rnd.next(6);
    if (mode == 0) {
        n = rnd.any(fixed);
    } else if (mode == 1) {
        n = nearPowerOfTen();
    } else if (mode == 2) {
        n = cascadeNumber();
    } else if (mode == 3) {
        n = stableNumber();
    } else {
        n = randomNumberWithDigits(rnd.next(1, 15));
    }

    println(n);
    return 0;
}
