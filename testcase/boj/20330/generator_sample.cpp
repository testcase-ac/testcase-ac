#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const long long MAX_N = 999999999999999999LL;

long long pow10ll(int exp) {
    long long value = 1;
    for (int i = 0; i < exp; ++i) value *= 10;
    return value;
}

long long randomNumberWithDigits(int digits) {
    string s;
    s.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < digits; ++i) s.push_back(char('0' + rnd.next(10)));
    return stoll(s);
}

long long randomPalindrome(int digits) {
    string s(digits, '0');
    for (int i = 0; i < (digits + 1) / 2; ++i) {
        int lo = (i == 0 ? 1 : 0);
        char c = char('0' + rnd.next(lo, 9));
        s[i] = c;
        s[digits - 1 - i] = c;
    }
    return stoll(s);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    long long n;

    if (mode == 0) {
        n = rnd.next(1, 1000);
    } else if (mode == 1) {
        int exp = rnd.next(0, 17);
        long long base = pow10ll(exp);
        long long delta = rnd.next(-3, 3);
        n = min(MAX_N, max(1LL, base + delta));
    } else if (mode == 2) {
        int digits = rnd.next(1, 18);
        n = randomPalindrome(digits);
    } else if (mode == 3) {
        int digits = rnd.next(2, 18);
        long long base = randomPalindrome(digits);
        long long delta = rnd.next(1, 999);
        if (rnd.next(2) == 0) delta = -delta;
        n = min(MAX_N, max(1LL, base + delta));
    } else if (mode == 4) {
        int digits = rnd.next(1, 18);
        long long lo = (digits == 1 ? 1 : pow10ll(digits - 1));
        long long hi = min(MAX_N, pow10ll(digits) - 1);
        n = rnd.next(lo, hi);
    } else if (mode == 5) {
        vector<long long> special = {
            1,
            9,
            10,
            11,
            99,
            100,
            101,
            999,
            1000,
            1001,
            999999999999999999LL,
            100000000000000000LL,
            99999999999999999LL
        };
        n = rnd.any(special);
    } else {
        long long prefix = randomNumberWithDigits(rnd.next(1, 9));
        long long scale = pow10ll(rnd.next(1, 9));
        long long suffix = rnd.next(0LL, scale - 1);
        n = min(MAX_N, max(1LL, prefix * scale + suffix));
    }

    println(n);
    return 0;
}
