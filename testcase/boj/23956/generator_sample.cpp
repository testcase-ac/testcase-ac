#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

namespace {

const long long kMaxValue = 1000000000000000000LL;

bool isLegal(long long value) {
    if (value < 1 || value > kMaxValue || value % 9 == 0) return false;
    return to_string(value).find('9') == string::npos;
}

long long nextLegal(long long value) {
    do {
        ++value;
    } while (!isLegal(value));
    return value;
}

long long randomLegalWithDigits(int digits) {
    while (true) {
        string value;
        value.push_back(char('1' + rnd.next(8)));
        for (int i = 1; i < digits; ++i) value.push_back(char('0' + rnd.next(9)));

        long long result = stoll(value);
        if (isLegal(result)) return result;
    }
}

long long randomLegalBelow(long long highExclusive) {
    while (true) {
        int digits = rnd.next(1, 18);
        long long value = randomLegalWithDigits(digits);
        if (value < highExclusive) return value;
    }
}

pair<long long, long long> shortRunCase() {
    long long f = randomLegalBelow(1000000);
    int steps = rnd.next(1, 20);
    long long l = f;
    for (int i = 0; i < steps; ++i) l = nextLegal(l);
    return {f, l};
}

pair<long long, long long> smallCase() {
    long long f = randomLegalBelow(1000);
    long long l = f;
    int steps = rnd.next(1, 40);
    for (int i = 0; i < steps; ++i) l = nextLegal(l);
    return {f, l};
}

pair<long long, long long> powerBoundaryCase() {
    int exponent = rnd.next(1, 17);
    long long power = 1;
    for (int i = 0; i < exponent; ++i) power *= 10;

    long long f = randomLegalWithDigits(exponent);
    long long l = nextLegal(power + rnd.next(0, 25));
    return {f, l};
}

pair<long long, long long> largeCase() {
    long long a = randomLegalWithDigits(rnd.next(15, 18));
    long long b = randomLegalWithDigits(rnd.next(15, 18));
    if (a == b) b = randomLegalWithDigits(18);
    if (a > b) swap(a, b);
    return {a, b};
}

pair<long long, long long> upperLimitCase() {
    long long l = kMaxValue;
    long long f = randomLegalWithDigits(18);
    return {f, l};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 60);
    vector<pair<long long, long long>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(5);
        if (mode == 0) {
            cases.push_back(smallCase());
        } else if (mode == 1) {
            cases.push_back(shortRunCase());
        } else if (mode == 2) {
            cases.push_back(powerBoundaryCase());
        } else if (mode == 3) {
            cases.push_back(largeCase());
        } else {
            cases.push_back(upperLimitCase());
        }
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const auto& testCase : cases) {
        ensuref(isLegal(testCase.first), "generated illegal F=%lld", testCase.first);
        ensuref(isLegal(testCase.second), "generated illegal L=%lld", testCase.second);
        ensuref(testCase.first < testCase.second, "generated non-increasing case");
        println(testCase.first, testCase.second);
    }

    return 0;
}
