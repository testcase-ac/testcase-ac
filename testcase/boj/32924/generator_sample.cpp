#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using TestCase = vector<pair<int, int>>;

TestCase makeFeasibleCase() {
    int n = rnd.next(1, 12);
    int groups = rnd.next(1, min(n, 5));
    vector<int> ds;
    int d = rnd.next(0, 20);
    for (int i = 0; i < groups; ++i) {
        ds.push_back(d);
        d += rnd.next(1, 12);
    }
    reverse(ds.begin(), ds.end());

    TestCase tc;
    int remaining = n;
    int high = rnd.next(40, 200);
    for (int g = 0; g < groups; ++g) {
        int cnt = (g + 1 == groups) ? remaining : rnd.next(1, remaining - (groups - g - 1));
        remaining -= cnt;

        int upper = max(1, high);
        int lower = max(1, upper - rnd.next(0, 20));
        for (int i = 0; i < cnt; ++i) {
            int h = rnd.next(lower, upper);
            tc.push_back({h, h + ds[g]});
        }
        high = max(1, lower - rnd.next(1, 8));
    }

    shuffle(tc.begin(), tc.end());
    return tc;
}

TestCase makeUnchangedCase() {
    int n = rnd.next(1, 12);
    TestCase tc;
    for (int i = 0; i < n; ++i) {
        int h = rnd.next(1, 1000000);
        tc.push_back({h, h});
    }
    return tc;
}

TestCase makePastLowerCase() {
    int n = rnd.next(1, 10);
    TestCase tc;
    int bad = rnd.next(n);
    for (int i = 0; i < n; ++i) {
        int h = rnd.next(2, 1000000);
        int p = h + rnd.next(0, min(20, 1000000 - h));
        if (i == bad) p = h - rnd.next(1, min(20, h - 1));
        tc.push_back({h, p});
    }
    return tc;
}

TestCase makeOrderTrapCase() {
    int n = rnd.next(2, 12);
    TestCase tc;
    int lowH = rnd.next(1, 50);
    int highH = rnd.next(lowH + 1, lowH + 60);
    int highD = rnd.next(2, 30);
    int lowD = rnd.next(0, highD - 1);
    tc.push_back({lowH, lowH + highD});
    tc.push_back({highH, highH + lowD});
    for (int i = 2; i < n; ++i) {
        int h = rnd.next(1, 120);
        int d = rnd.next(0, 30);
        tc.push_back({h, h + d});
    }
    shuffle(tc.begin(), tc.end());
    return tc;
}

TestCase makeBoundaryCase() {
    vector<int> values = {1, 2, 999999, 1000000};
    int n = rnd.next(1, 8);
    TestCase tc;
    for (int i = 0; i < n; ++i) {
        int h = rnd.any(values);
        int p = rnd.next(h, 1000000);
        if (rnd.next(3) == 0) p = h;
        tc.push_back({h, p});
    }
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<TestCase> tests;
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        if (mode == 0) tests.push_back(makeFeasibleCase());
        else if (mode == 1) tests.push_back(makeUnchangedCase());
        else if (mode == 2) tests.push_back(makePastLowerCase());
        else if (mode == 3) tests.push_back(makeOrderTrapCase());
        else tests.push_back(makeBoundaryCase());
    }

    println((int)tests.size());
    for (const auto& tc : tests) {
        vector<int> h, p;
        for (auto [cur, past] : tc) {
            h.push_back(cur);
            p.push_back(past);
        }
        println((int)tc.size());
        println(h);
        println(p);
    }

    return 0;
}
