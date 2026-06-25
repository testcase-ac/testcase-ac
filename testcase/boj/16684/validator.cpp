#include "testlib.h"

#include <algorithm>
#include <array>
#include <string>

using namespace std;

using i128 = __int128_t;

i128 parseNonnegative(const string& s) {
    ensuref(!s.empty(), "k must not be empty");
    ensuref(s == "0" || s[0] != '0', "k has leading zero: %s", s.c_str());

    i128 value = 0;
    for (char c : s) {
        ensuref('0' <= c && c <= '9', "k contains a non-digit character");
        value = value * 10 + (c - '0');
    }
    return value;
}

i128 powInt(int base, int exponent) {
    i128 result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

i128 clockwiseDistance(int from, int to) {
    return from <= to ? to - from : to - from + 3;
}

i128 cyclicMoveCount(int n, int from, int to, array<array<array<i128, 4>, 4>, 31>& memo) {
    if (n == 1) {
        return clockwiseDistance(from, to);
    }

    i128& result = memo[n][from][to];
    if (result != -1) {
        return result;
    }

    int middle = from ^ to;
    if (clockwiseDistance(from, to) == 1) {
        result = cyclicMoveCount(n - 1, from, middle, memo) + 1 +
                 cyclicMoveCount(n - 1, middle, to, memo);
    } else {
        result = cyclicMoveCount(n - 1, from, to, memo) + 1 +
                 cyclicMoveCount(n - 1, to, from, memo) + 1 +
                 cyclicMoveCount(n - 1, from, to, memo);
    }
    return result;
}

i128 maxKFor(int m, int n) {
    if (m == 1) {
        return powInt(2, n) - 1;
    }
    if (m == 2) {
        return powInt(3, n) - 1;
    }

    array<array<array<i128, 4>, 4>, 31> memo;
    for (auto& byN : memo) {
        for (auto& byFrom : byN) {
            fill(byFrom.begin(), byFrom.end(), -1);
        }
    }
    return cyclicMoveCount(n, 1, 3, memo) - 1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 3, "m");
    inf.readSpace();

    int n;
    if (m == 1) {
        n = inf.readInt(1, 60, "n");
    } else if (m == 2) {
        n = inf.readInt(1, 40, "n");
    } else {
        n = inf.readInt(1, 30, "n");
    }

    inf.readSpace();
    string kToken = inf.readToken("[0-9]{1,40}", "k");
    inf.readEoln();

    i128 k = parseNonnegative(kToken);
    ensuref(k <= maxKFor(m, n), "k is too large for m=%d, n=%d", m, n);

    inf.readEof();
}
