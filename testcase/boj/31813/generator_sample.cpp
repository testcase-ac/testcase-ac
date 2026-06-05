#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

long long toNumber(const string& s) {
    long long value = 0;
    for (char c : s) {
        value = value * 10 + (c - '0');
    }
    return value;
}

long long pow10(int n) {
    long long value = 1;
    for (int i = 0; i < n; ++i) {
        value *= 10;
    }
    return value;
}

long long makeRunNumber(int n) {
    char digit = char('1' + rnd.next(9));
    return toNumber(string(n, digit));
}

long long makeMonotoneNumber(int n) {
    string s;
    int last = rnd.next(1, 9);
    s.push_back(char('0' + last));
    for (int i = 1; i < n; ++i) {
        last = rnd.next(last, 9);
        s.push_back(char('0' + last));
    }
    return toNumber(s);
}

long long makeDigitPatternNumber(int n) {
    string s;
    int mode = rnd.next(4);

    for (int i = 0; i < n; ++i) {
        int digit;
        if (mode == 0) {
            digit = (i % 2 == 0 ? rnd.next(1, 9) : rnd.next(0, 2));
        } else if (mode == 1) {
            digit = (i % 2 == 0 ? rnd.next(7, 9) : rnd.next(0, 9));
        } else if (mode == 2) {
            digit = rnd.next(0, 1) ? 9 : 0;
        } else {
            digit = rnd.next(0, 9);
        }
        if (i == 0 && digit == 0) {
            digit = rnd.next(1, 9);
        }
        s.push_back(char('0' + digit));
    }

    return toNumber(s);
}

long long makeCaseValue(int n) {
    long long lo = pow10(n - 1);
    long long hi = pow10(n) - 1;

    int mode = rnd.next(8);
    if (mode == 0) {
        return lo;
    }
    if (mode == 1) {
        return hi;
    }
    if (mode == 2) {
        return rnd.next(lo, min(hi, lo + 30));
    }
    if (mode == 3) {
        return rnd.next(max(lo, hi - 30), hi);
    }
    if (mode == 4) {
        return makeRunNumber(n);
    }
    if (mode == 5) {
        return makeMonotoneNumber(n);
    }
    if (mode == 6) {
        return makeDigitPatternNumber(n);
    }
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        int sizeMode = rnd.next(5);
        if (sizeMode == 0) {
            n = 1;
        } else if (sizeMode == 1) {
            n = rnd.next(2, 5);
        } else if (sizeMode == 2) {
            n = rnd.next(6, 10);
        } else if (sizeMode == 3) {
            n = rnd.next(11, 16);
        } else {
            n = 17;
        }

        long long k = makeCaseValue(n);
        println(n, k);
    }

    return 0;
}
