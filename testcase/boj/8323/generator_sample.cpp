#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int k;
};

int clampValue(long long value) {
    return int(max(1LL, min(1000000LL, value)));
}

TestCase randomReachableCase(int n) {
    long long low = n;
    long long high = min(1000000LL, 6LL * n);
    return {n, int(rnd.next(low, high))};
}

TestCase randomCaseForMode(int mode) {
    int n;

    switch (mode) {
        case 0:
            n = rnd.next(1, 12);
            return randomReachableCase(n);
        case 1:
            n = rnd.next(1, 12);
            return {n, rnd.next(1, 6 * n)};
        case 2:
            n = rnd.next(2, 200);
            return {n, rnd.next(1, n - 1)};
        case 3:
            n = rnd.next(1, 200000);
            return {n, clampValue(6LL * n + rnd.next(1, 200))};
        case 4:
            n = rnd.next(900000, 1000000);
            return {n, rnd.next(1, 1000000)};
        case 5:
            n = rnd.next(1, 1000000);
            return {n, rnd.any(vector<int>{1, n, clampValue(6LL * n), 1000000})};
        default:
            n = rnd.next(1, 1000000);
            return {n, rnd.next(1, 1000000)};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    vector<TestCase> cases;

    vector<TestCase> anchors = {
        {1, rnd.next(1, 6)},
        {rnd.next(1, 20), 1},
        {rnd.next(1, 20), 1000000},
        {1000000, rnd.any(vector<int>{1, 1000000})},
    };
    shuffle(anchors.begin(), anchors.end());

    for (const TestCase& testCase : anchors) {
        if ((int)cases.size() == t) break;
        cases.push_back(testCase);
    }

    while ((int)cases.size() < t) {
        cases.push_back(randomCaseForMode(rnd.next(0, 6)));
    }
    shuffle(cases.begin(), cases.end());

    println(t);
    for (const TestCase& testCase : cases) {
        println(testCase.n, testCase.k);
    }

    return 0;
}
