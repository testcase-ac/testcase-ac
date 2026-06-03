#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

const int kMinValue = -6000000;
const int kMaxValue = 6000000;

int randomNonZero(int lo, int hi) {
    int x = 0;
    while (x == 0) {
        x = rnd.next(lo, hi);
    }
    return x;
}

int clampToLimit(long long x) {
    return (int)max<long long>(kMinValue, min<long long>(kMaxValue, x));
}

tuple<int, int, int> makeMemberCase() {
    int d = randomNonZero(-20, 20);
    int n = rnd.next(1, 20);
    int a = rnd.next(-100, 100);
    long long v = (long long)a + (long long)(n - 1) * d;

    if (rnd.next(5) == 0) {
        a = rnd.any(vector<int>{kMinValue, kMaxValue, -1, 0, 1});
        d = randomNonZero(-6000000, 6000000);
        n = rnd.next(1, 3);
        v = (long long)a + (long long)(n - 1) * d;
    }

    while (v < kMinValue || v > kMaxValue) {
        d = randomNonZero(-20, 20);
        n = rnd.next(1, 20);
        a = rnd.next(-100, 100);
        v = (long long)a + (long long)(n - 1) * d;
    }

    return {a, d, (int)v};
}

tuple<int, int, int> makeNonMemberCase() {
    int a = rnd.next(-200, 200);
    int d = randomNonZero(-30, 30);
    int n = rnd.next(-10, 25);
    int offset = randomNonZero(-5, 5);
    long long v = (long long)a + (long long)n * d + offset;

    while (v < kMinValue || v > kMaxValue || ((v - a) % d == 0 && (v - a) / d >= 0)) {
        a = rnd.next(-200, 200);
        d = randomNonZero(-30, 30);
        n = rnd.next(-10, 25);
        offset = randomNonZero(-5, 5);
        v = (long long)a + (long long)n * d + offset;
    }

    return {a, d, (int)v};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(3, 12);
    vector<tuple<int, int, int>> cases;

    cases.push_back(makeMemberCase());
    cases.push_back(makeNonMemberCase());
    cases.push_back({0, randomNonZero(-5, 5), rnd.next(-10, 10)});
    cases.push_back({rnd.any(vector<int>{kMinValue, kMaxValue}), randomNonZero(-6000000, 6000000), rnd.next(kMinValue, kMaxValue)});

    while ((int)cases.size() < caseCount) {
        if (rnd.next(2) == 0) {
            cases.push_back(makeMemberCase());
        } else {
            cases.push_back(makeNonMemberCase());
        }
    }

    shuffle(cases.begin(), cases.end());
    for (auto [a, d, v] : cases) {
        println(a, d, clampToLimit(v));
    }
    println(0, 0, 0);

    return 0;
}
