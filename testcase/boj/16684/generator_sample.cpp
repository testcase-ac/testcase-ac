#include "testlib.h"

#include <algorithm>
#include <array>
#include <string>
#include <vector>

using namespace std;

using i128 = __int128_t;

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

string toString(i128 value) {
    if (value == 0) {
        return "0";
    }

    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

i128 randomUpTo(i128 high) {
    string decimal = toString(high);
    while (true) {
        string candidate;
        for (int i = 0; i < int(decimal.size()); ++i) {
            candidate.push_back(char('0' + rnd.next(0, 9)));
        }
        if (candidate.size() > 1 && candidate[0] == '0') {
            candidate[0] = char('1' + rnd.next(0, 8));
        }

        i128 value = 0;
        for (char c : candidate) {
            value = value * 10 + (c - '0');
        }
        if (value <= high) {
            return value;
        }
    }
}

int maxNFor(int m) {
    if (m == 1) {
        return 60;
    }
    if (m == 2) {
        return 40;
    }
    return 30;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(1, 3);
    int nLimit = maxNFor(m);
    int mode = rnd.next(0, 7);

    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = nLimit;
    } else if (mode <= 3) {
        n = rnd.next(1, min(nLimit, 8));
    } else {
        n = rnd.next(1, nLimit);
    }

    i128 maxK = maxKFor(m, n);
    vector<i128> special = {0, maxK};
    for (i128 delta = 1; delta <= 3 && delta <= maxK; ++delta) {
        special.push_back(delta);
        special.push_back(maxK - delta);
    }

    i128 k;
    if (mode <= 1) {
        k = rnd.any(special);
    } else if (mode <= 3) {
        k = rnd.next(0, int(min<i128>(maxK, 1000)));
    } else if (mode <= 5 && maxK > 0) {
        i128 window = min<i128>(maxK, 1000);
        k = maxK - rnd.next(0, int(window));
    } else {
        k = randomUpTo(maxK);
    }

    println(m, n, toString(k));
    return 0;
}
