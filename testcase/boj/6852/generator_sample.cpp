#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct TestCase {
    int n;
    int k;
    int w;
    vector<int> scores;
};

static vector<int> makeScores(int n, int mode) {
    vector<int> scores(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            scores[i] = rnd.next(-8, 15);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            scores[i] = (i % 2 == 0) ? rnd.next(4, 30) : rnd.next(-30, -1);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            scores[i] = rnd.next(-20, -1);
        }
        int positives = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < positives; ++i) {
            scores[rnd.next(0, n - 1)] = rnd.next(20, 80);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            scores[i] = rnd.next(0, 12);
        }
        int penalties = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < penalties; ++i) {
            scores[rnd.next(0, n - 1)] = rnd.next(-80, -10);
        }
    } else {
        int low = rnd.next(-10000, -1);
        int high = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            scores[i] = rnd.next(0, 3) == 0 ? rnd.next(low, high) : rnd.next(-50, 50);
        }
    }

    return scores;
}

static TestCase makeCase(int mode) {
    TestCase tc;

    if (mode == 0) {
        tc.n = rnd.next(1, 3);
        tc.k = rnd.next(1, 500);
        tc.w = rnd.next(1, 100);
    } else if (mode == 1) {
        tc.n = rnd.next(4, 12);
        tc.k = rnd.next(1, 4);
        tc.w = rnd.next(1, min(6, tc.n));
    } else if (mode == 2) {
        tc.n = rnd.next(8, 24);
        tc.k = rnd.next(2, 8);
        tc.w = rnd.next(2, min(10, tc.n));
    } else if (mode == 3) {
        tc.n = rnd.next(15, 40);
        tc.k = rnd.next(1, 12);
        tc.w = rnd.next(1, 12);
    } else {
        tc.n = rnd.next(35, 80);
        tc.k = rnd.next(1, 20);
        tc.w = rnd.next(1, 20);
    }

    tc.scores = makeScores(tc.n, mode);
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 7);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        TestCase tc = makeCase(caseIndex % 5);
        println(tc.n, tc.k, tc.w);
        for (int score : tc.scores) {
            println(score);
        }
    }

    return 0;
}
