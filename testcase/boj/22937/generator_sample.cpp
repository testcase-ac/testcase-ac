#include "testlib.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const long long SCALE = 1000000000LL;
const long long LIMIT = 4 * SCALE;

string formatDecimal(long long value) {
    long long absValue = llabs(value);
    string result;
    if (value < 0) {
        result += '-';
    }
    result += char('0' + absValue / SCALE);
    result += '.';
    string frac = to_string(absValue % SCALE);
    result += string(9 - frac.size(), '0') + frac;
    return result;
}

long long randomScaledInRange(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

long long nonzeroFrom(const vector<long long>& values) {
    long long value = rnd.any(values);
    if (value == 0) {
        return rnd.next(0, 1) == 0 ? -1 : 1;
    }
    return value;
}

pair<long long, long long> makePair(int mode) {
    vector<long long> edges = {
        -LIMIT, -LIMIT + 1, -3 * SCALE, -SCALE, -1,
        0,
        1, SCALE, 3 * SCALE, LIMIT - 1, LIMIT
    };

    if (mode == 0) {
        return {rnd.any(edges), rnd.any(edges)};
    }

    if (mode == 1) {
        long long a = rnd.next(-20LL, 20LL);
        long long b = rnd.next(-20LL, 20LL);
        return {a, b};
    }

    if (mode == 2) {
        long long integerPart = rnd.next(-4, 4);
        long long frac = rnd.next(0LL, SCALE - 1);
        long long value = llabs(integerPart) * SCALE + frac;
        if (integerPart < 0) {
            value = -value;
        } else if (integerPart == 0 && rnd.next(0, 1) == 0) {
            value = -value;
        }
        value = max(-LIMIT, min(LIMIT, value));
        return {value, nonzeroFrom(edges)};
    }

    if (mode == 3) {
        long long a = rnd.next(LIMIT - 1000000, LIMIT);
        long long b = rnd.next(LIMIT - 1000000, LIMIT);
        if (rnd.next(0, 1) == 0) {
            a = -a;
        }
        if (rnd.next(0, 1) == 0) {
            b = -b;
        }
        return {a, b};
    }

    if (mode == 4) {
        long long a = rnd.next(-4LL, 4LL) * SCALE + rnd.next(-999LL, 999LL);
        long long b = rnd.next(-4LL, 4LL) * SCALE + rnd.next(-999999LL, 999999LL);
        a = max(-LIMIT, min(LIMIT, a));
        b = max(-LIMIT, min(LIMIT, b));
        return {a, b};
    }

    return {randomScaledInRange(-LIMIT, LIMIT), randomScaledInRange(-LIMIT, LIMIT)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 6) {
        n = rnd.next(2, 12);
    } else if (sizeMode <= 8) {
        n = rnd.next(13, 40);
    } else {
        n = rnd.next(80, 160);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 5);
        pair<long long, long long> values = makePair(mode);
        cout << formatDecimal(values.first) << ' ' << formatDecimal(values.second) << '\n';
    }

    return 0;
}
