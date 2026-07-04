#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long pow10(int exponent) {
    long long value = 1;
    for (int i = 0; i < exponent; ++i) value *= 10;
    return value;
}

long long clampRange(long long value) {
    return max(1LL, min(LIMIT, value));
}

pair<long long, long long> orderedRange(long long a, long long b) {
    a = clampRange(a);
    b = clampRange(b);
    if (a > b) swap(a, b);
    return {a, b};
}

long long randomWithDigits(int digits) {
    if (digits == 1) return rnd.next(1LL, 9LL);

    long long low = pow10(digits - 1);
    long long high = min(LIMIT, pow10(digits) - 1);
    return rnd.next(low, high);
}

long long makeSameEdgeDigit(int digits) {
    if (digits == 1) return rnd.next(1LL, 9LL);

    int edge = rnd.next(1, 9);
    string s(digits, '0');
    s.front() = char('0' + edge);
    s.back() = char('0' + edge);
    for (int i = 1; i + 1 < digits; ++i) s[i] = char('0' + rnd.next(0, 9));
    return stoll(s);
}

pair<long long, long long> randomCase() {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        long long l = rnd.next(1LL, 25LL);
        return orderedRange(l, l + rnd.next(0LL, 30LL));
    }

    if (mode == 1) {
        int digits = rnd.next(1, 18);
        long long center = randomWithDigits(digits);
        long long width = rnd.next(0LL, min(2000LL, center - 1));
        return orderedRange(center - width, center + rnd.next(0LL, 2000LL));
    }

    if (mode == 2) {
        int digits = rnd.next(1, 18);
        long long boundary = digits == 18 ? LIMIT : pow10(digits);
        long long left = boundary - rnd.next(0LL, 1000LL);
        long long right = boundary + rnd.next(0LL, 1000LL);
        return orderedRange(left, right);
    }

    if (mode == 3) {
        int digits = rnd.next(1, 18);
        long long target = makeSameEdgeDigit(digits);
        long long radius = rnd.next(0LL, 500LL);
        return orderedRange(target - radius, target + radius);
    }

    if (mode == 4) {
        long long r = LIMIT - rnd.next(0LL, 1000000LL);
        long long l = r - rnd.next(0LL, 1000000LL);
        return orderedRange(l, r);
    }

    long long l = rnd.next(1LL, LIMIT);
    long long r = rnd.next(l, LIMIT);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(15, 60);
    vector<pair<long long, long long>> cases;
    cases.push_back({1, 1});
    cases.push_back({8, 25});
    cases.push_back({12, 21});
    cases.push_back({LIMIT - 1000, LIMIT});

    while ((int)cases.size() < t) cases.push_back(randomCase());
    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& test : cases) println(test.first, test.second);

    return 0;
}
