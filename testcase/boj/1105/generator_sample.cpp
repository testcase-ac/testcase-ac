#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

const long long MAX_VALUE = 2000000000LL;

long long pow10ll(int exponent) {
    long long value = 1;
    while (exponent--) value *= 10;
    return value;
}

long long randomNumberWithDigits(int digits) {
    long long lo = digits == 1 ? 1 : pow10ll(digits - 1);
    long long hi = digits == 10 ? MAX_VALUE : pow10ll(digits) - 1;
    return rnd.next(lo, hi);
}

long long parseBounded(const string& s) {
    long long value = 0;
    for (char c : s) value = value * 10 + (c - '0');
    return value;
}

char randomDigit(bool first) {
    if (first) return char('1' + rnd.next(9));
    return char('0' + rnd.next(10));
}

char randomEightBiasedDigit(bool first) {
    if (rnd.next(100) < 55) return '8';
    return randomDigit(first);
}

pair<long long, long long> randomSharedPrefixRange() {
    while (true) {
        int digits = rnd.next(1, 10);
        int common = rnd.next(0, digits - 1);
        string left, right;

        for (int i = 0; i < common; ++i) {
            char c = randomEightBiasedDigit(i == 0);
            left += c;
            right += c;
        }

        int minLeftDigit = common == 0 ? 1 : 0;
        int a = rnd.next(minLeftDigit, 8);
        int b = rnd.next(a + 1, 9);
        left += char('0' + a);
        right += char('0' + b);

        while ((int)left.size() < digits) left += randomEightBiasedDigit(false);
        while ((int)right.size() < digits) right += randomEightBiasedDigit(false);

        long long L = parseBounded(left);
        long long R = parseBounded(right);
        if (1 <= L && L <= R && R <= MAX_VALUE) return {L, R};
    }
}

pair<long long, long long> randomAroundEightBlock() {
    int digits = rnd.next(1, 9);
    long long center = 0;
    for (int i = 0; i < digits; ++i) center = center * 10 + 8;

    long long radius = rnd.next(0LL, min(5000LL, center - 1));
    long long extra = rnd.next(0LL, 5000LL);
    long long L = max(1LL, center - radius);
    long long R = min(MAX_VALUE, center + extra);
    return {L, R};
}

pair<long long, long long> randomAcrossDigitBoundary() {
    int digits = rnd.next(1, 9);
    long long boundary = pow10ll(digits);
    long long before = rnd.next(0LL, min(2000LL, boundary - 1));
    long long after = rnd.next(0LL, 2000LL);
    long long L = max(1LL, boundary - before);
    long long R = min(MAX_VALUE, boundary + after);
    return {L, R};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long L, R;
    int mode = rnd.next(5);

    if (mode == 0) {
        L = R = randomNumberWithDigits(rnd.next(1, 10));
    } else if (mode == 1) {
        tie(L, R) = randomSharedPrefixRange();
    } else if (mode == 2) {
        tie(L, R) = randomAroundEightBlock();
    } else if (mode == 3) {
        tie(L, R) = randomAcrossDigitBoundary();
    } else {
        L = rnd.next(1LL, MAX_VALUE);
        R = rnd.next(L, MAX_VALUE);
    }

    println(L, R);
    return 0;
}
