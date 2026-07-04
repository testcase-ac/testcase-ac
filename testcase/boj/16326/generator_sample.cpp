#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long pow10ll(int exponent) {
    long long value = 1;
    for (int i = 0; i < exponent; i++) value *= 10;
    return value;
}

long long makePalindrome(int digits) {
    string s(digits, '0');
    s[0] = char('1' + rnd.next(0, 8));
    for (int i = 1; i < (digits + 1) / 2; i++) {
        s[i] = char('0' + rnd.next(0, 9));
    }
    for (int i = 0; i < digits / 2; i++) {
        s[digits - 1 - i] = s[i];
    }
    return stoll(s);
}

long long boundedShift(long long center, long long radius) {
    long long lo = max(1LL, center - radius);
    long long hi = min(LIMIT, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> samples = {156, 9524, 42657, 5735832847451LL};
    int mode = rnd.next(0, 7);
    long long n = 1;

    if (mode == 0) {
        n = rnd.next(1LL, 1000LL);
    } else if (mode == 1) {
        n = boundedShift(rnd.any(samples), 200);
    } else if (mode == 2) {
        int exponent = rnd.next(1, 18);
        long long center = pow10ll(exponent);
        long long radius = min(1000000LL, center - 1);
        n = boundedShift(center, radius);
    } else if (mode == 3) {
        int digits = rnd.next(1, 18);
        n = makePalindrome(digits);
    } else if (mode == 4) {
        int firstDigits = rnd.next(1, 18);
        int secondDigits = rnd.next(1, 18);
        long long a = makePalindrome(firstDigits);
        long long b = makePalindrome(secondDigits);
        while (a > LIMIT - b) {
            firstDigits = rnd.next(1, 17);
            secondDigits = rnd.next(1, 17);
            a = makePalindrome(firstDigits);
            b = makePalindrome(secondDigits);
        }
        n = a + b;
    } else if (mode == 5) {
        int digits = rnd.next(1, 18);
        long long upper = pow10ll(digits) - 1;
        long long lower = digits == 1 ? 1 : pow10ll(digits - 1);
        n = rnd.next(lower, upper);
    } else if (mode == 6) {
        long long edge = rnd.next(0, 1) == 0 ? 1 : LIMIT;
        n = boundedShift(edge, 1000000);
    } else {
        n = rnd.next(1LL, LIMIT);
    }

    println(n);
    return 0;
}
