#include "testlib.h"
#include <vector>

using namespace std;

struct TestCase {
    int n;
    int k;
    vector<int> b;
};

TestCase makeZeros() {
    int n = rnd.next(1, 12);
    int k = rnd.next(1, 30);
    return {n, k, vector<int>(n, 0)};
}

TestCase makeSingleSegment() {
    int n = rnd.next(2, 18);
    int k = rnd.next(1, 80);
    vector<int> b(n, 0);
    int l = rnd.next(0, n - 1);
    int r = rnd.next(l, n - 1);
    int remaining = k;
    for (int i = l; i <= r; ++i) {
        int slots = r - i + 1;
        b[i] = (i == r) ? remaining : rnd.next(0, remaining);
        remaining -= b[i];
        if (remaining > 0 && slots == 1) b[i] = remaining;
    }
    shuffle(b.begin() + l, b.begin() + r + 1);
    return {n, k, b};
}

TestCase makeTwoSegments() {
    int n = rnd.next(6, 22);
    int k = rnd.next(4, 120);
    vector<int> b(n, 0);

    int gapLeft = rnd.next(1, n - 4);
    int gapRight = rnd.next(gapLeft + 1, n - 3);
    int l1 = rnd.next(0, gapLeft - 1);
    int r1 = gapLeft - 1;
    int l2 = gapRight + 1;
    int r2 = rnd.next(l2, n - 1);

    int firstSum = rnd.next(1, k - 1);
    int secondSum = k - firstSum;
    b[r1] = firstSum;
    b[r2] = secondSum;

    for (int i = l1; i < r1; ++i) {
        int take = rnd.next(0, b[r1]);
        b[i] = take;
        b[r1] -= take;
    }
    for (int i = l2; i < r2; ++i) {
        int take = rnd.next(0, b[r2]);
        b[i] = take;
        b[r2] -= take;
    }

    b[rnd.next(gapLeft, gapRight)] = rnd.next(1, k);
    for (int i = 0; i < n; ++i) {
        if (b[i] == 0 && rnd.next(0, 3) == 0) b[i] = rnd.next(0, k);
    }

    return {n, k, b};
}

TestCase makeRandomSmall() {
    int n = rnd.next(1, 30);
    int k = rnd.next(1, 150);
    vector<int> b(n);
    int maxValue = rnd.next(0, k);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 4) == 0) {
            b[i] = 0;
        } else {
            b[i] = rnd.next(0, maxValue);
        }
    }
    return {n, k, b};
}

TestCase makeDenseMedium() {
    int n = rnd.next(80, 180);
    int k = rnd.next(100, 1000);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 9) == 0) {
            b[i] = 0;
        } else {
            b[i] = rnd.next(1, k);
        }
    }
    return {n, k, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 10);
    vector<TestCase> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 4);
        if (mode == 0) cases.push_back(makeZeros());
        if (mode == 1) cases.push_back(makeSingleSegment());
        if (mode == 2) cases.push_back(makeTwoSegments());
        if (mode == 3) cases.push_back(makeRandomSmall());
        if (mode == 4) cases.push_back(makeDenseMedium());
    }

    println(t);
    for (const TestCase& tc : cases) {
        println(tc.n, tc.k);
        println(tc.b);
    }

    return 0;
}
