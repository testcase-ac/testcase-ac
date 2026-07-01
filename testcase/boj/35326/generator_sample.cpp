#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long smallValue() {
    return rnd.next(0, 30);
}

long long positiveSmallValue() {
    return rnd.next(1, 30);
}

long long largeValue() {
    return rnd.next(900000000LL, 1000000000LL);
}

struct TestCase {
    long long A;
    long long B;
    long long cA;
    long long cB;
    long long fA;
};

TestCase randomCase() {
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        return {smallValue(), smallValue(), positiveSmallValue(), positiveSmallValue(), smallValue()};
    }
    if (mode == 1) {
        long long cA = positiveSmallValue();
        long long cB = positiveSmallValue();
        long long fA = rnd.next(1, 80);
        long long A = max(0LL, fA - rnd.next(0, 10));
        long long B = rnd.next(0LL, cB + 10);
        return {A, B, cA, cB, fA};
    }
    if (mode == 2) {
        long long cA = positiveSmallValue();
        long long cB = positiveSmallValue();
        long long exchanges = rnd.next(0, 8);
        long long extraB = rnd.next(0LL, cB - 1);
        long long B = exchanges * cB + extraB;
        long long A = smallValue();
        long long fA = min(1000000000LL, A + exchanges * cA + rnd.next(0LL, cA + 10));
        return {A, B, cA, cB, fA};
    }
    if (mode == 3) {
        long long cA = rnd.next(1, 1000);
        long long cB = largeValue();
        long long A = rnd.next(0, 1000);
        long long B = rnd.next(0, 1000);
        long long fA = rnd.next(A, min(1000000000LL, A + 2000));
        return {A, B, cA, cB, fA};
    }
    if (mode == 4) {
        long long cA = largeValue();
        long long cB = rnd.next(1, 1000);
        long long A = rnd.next(0, 1000);
        long long B = rnd.next(0, 1000);
        long long fA = rnd.next(0, 1000000);
        return {A, B, cA, cB, fA};
    }
    if (mode == 5) {
        return {largeValue(), largeValue(), largeValue(), largeValue(), rnd.next(0LL, 1000000000LL)};
    }
    if (mode == 6) {
        long long cA = rnd.next(1LL, 1000000000LL);
        long long cB = rnd.next(1LL, 1000000000LL);
        long long fA = rnd.any(vector<long long>{0, 1, 1000000000LL});
        return {0, 0, cA, cB, fA};
    }

    long long cA = rnd.any(vector<long long>{1, 2, 3, 10, 1000000000LL});
    long long cB = rnd.any(vector<long long>{1, 2, 3, 10, 1000000000LL});
    long long A = rnd.any(vector<long long>{0, 1, 2, 999999999LL, 1000000000LL});
    long long B = rnd.any(vector<long long>{0, 1, 2, 999999999LL, 1000000000LL});
    long long fA = rnd.any(vector<long long>{0, 1, 2, 999999999LL, 1000000000LL});
    return {A, B, cA, cB, fA};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 35);
    vector<TestCase> tests;
    tests.push_back({0, 0, 1, 1, 0});
    tests.push_back({0, 0, 1, 1, 1});
    tests.push_back({0, 0, 1, 1000000000LL, 1000000000LL});
    tests.push_back({1000000000LL, 1000000000LL, 1000000000LL, 1000000000LL, 0});

    while ((int)tests.size() < t) {
        tests.push_back(randomCase());
    }
    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (const TestCase& tc : tests) {
        println(tc.A, tc.B, tc.cA, tc.cB, tc.fA);
    }

    return 0;
}
