#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000000000LL;

int64 pow10Int(int exponent) {
    int64 value = 1;
    for (int i = 0; i < exponent; ++i) value *= 10;
    return value;
}

bool isBoring(int64 value) {
    string digits = to_string(value);
    for (int i = 0; i < int(digits.size()); ++i) {
        int digit = digits[i] - '0';
        bool oddPosition = (i % 2 == 0);
        if (oddPosition != (digit % 2 == 1)) return false;
    }
    return true;
}

int64 randomBoringNumber(int length) {
    int64 value = 0;
    for (int i = 0; i < length; ++i) {
        int digit;
        if (i % 2 == 0) {
            digit = rnd.any(vector<int>{1, 3, 5, 7, 9});
        } else {
            digit = rnd.any(vector<int>{0, 2, 4, 6, 8});
        }
        value = value * 10 + digit;
    }
    return value;
}

pair<int64, int64> makeRangeAround(int64 center, int64 radius) {
    int64 left = max<int64>(1, center - rnd.next(0LL, radius));
    int64 right = min<int64>(LIMIT, center + rnd.next(0LL, radius));
    if (left > right) swap(left, right);
    return {left, right};
}

pair<int64, int64> randomCase() {
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int64 l = rnd.next(1LL, 300LL);
        int64 r = rnd.next(l, min<int64>(1000, l + rnd.next(0LL, 80LL)));
        return {l, r};
    }

    if (mode == 1) {
        int exponent = rnd.next(1, 18);
        int64 base = pow10Int(exponent);
        return makeRangeAround(base, rnd.next(0LL, min<int64>(500, base - 1)));
    }

    if (mode == 2) {
        int length = rnd.next(1, 18);
        int64 center = randomBoringNumber(length);
        return makeRangeAround(center, rnd.next(0LL, 300LL));
    }

    if (mode == 3) {
        int length = rnd.next(1, 18);
        int64 lo = pow10Int(length - 1);
        int64 hi = min<int64>(LIMIT, pow10Int(length) - 1);
        int64 l = rnd.next(lo, hi);
        int64 span = rnd.next(0LL, min<int64>(10000, hi - l));
        return {l, l + span};
    }

    if (mode == 4) {
        int64 r = rnd.next(max<int64>(1, LIMIT - 1000000), LIMIT);
        int64 l = rnd.next(max<int64>(1, r - 100000), r);
        return {l, r};
    }

    if (mode == 5) {
        int64 value = rnd.next(1LL, LIMIT);
        return {value, value};
    }

    int length = rnd.next(1, 18);
    int64 first = randomBoringNumber(length);
    int64 second = randomBoringNumber(length);
    if (first > second) swap(first, second);
    return {first, second};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 30);
    vector<pair<int64, int64>> cases;
    cases.push_back({1, 1});
    cases.push_back({5, 15});
    cases.push_back({120, 125});
    cases.push_back({779, 783});
    cases.push_back({LIMIT, LIMIT});

    while (int(cases.size()) < t) {
        pair<int64, int64> current = randomCase();
        if (current.first <= current.second && current.first >= 1 && current.second <= LIMIT) {
            cases.push_back(current);
        }
    }

    shuffle(cases.begin(), cases.end());

    println(int(cases.size()));
    for (const auto& current : cases) {
        println(current.first, current.second);
    }

    return 0;
}
