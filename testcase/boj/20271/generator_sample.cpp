#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    int n;
    int k1;
    int alpha;
};

int boundedAlpha(int n, int preferred) {
    return max(1, min({preferred, 100, n - 1}));
}

Case randomSmallCase() {
    int n = rnd.next(2, 200);
    int k1 = rnd.next(0, n - 1);
    int alpha = rnd.next(1, min(100, n - 1));
    return {n, k1, alpha};
}

Case randomStructuredCase() {
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 30);
    } else if (mode == 1) {
        n = rnd.next(2, 20) * rnd.next(2, 20);
    } else if (mode == 2) {
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
                              41, 43, 47, 53, 59, 61, 67, 71, 97};
        n = rnd.any(primes);
    } else if (mode == 3) {
        n = rnd.next(900, 1200);
    } else if (mode == 4) {
        n = rnd.next(99999900, 100000100);
    } else {
        n = rnd.next(199999800, 200000000);
    }

    int kMode = rnd.next(0, 4);
    int k1;
    if (kMode == 0) {
        k1 = 0;
    } else if (kMode == 1) {
        k1 = 1 % n;
    } else if (kMode == 2) {
        k1 = n - 1;
    } else if (kMode == 3) {
        k1 = n / 2;
    } else {
        k1 = rnd.next(0, n - 1);
    }

    int aMode = rnd.next(0, 5);
    int alpha;
    if (aMode == 0) {
        alpha = 1;
    } else if (aMode == 1) {
        alpha = boundedAlpha(n, 2);
    } else if (aMode == 2) {
        alpha = boundedAlpha(n, n - 1);
    } else if (aMode == 3) {
        alpha = boundedAlpha(n, 100);
    } else if (aMode == 4) {
        alpha = boundedAlpha(n, k1 + 1);
    } else {
        alpha = rnd.next(1, min(100, n - 1));
    }

    return {n, k1, alpha};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Case> cases;
    cases.push_back(randomSmallCase());
    cases.push_back(randomStructuredCase());
    cases.push_back({2, rnd.next(0, 1), 1});
    cases.push_back({rnd.next(95, 105), rnd.next(0, 94), rnd.next(1, 94)});
    cases.push_back({200000000, rnd.next(0, 199999999), rnd.next(1, 100)});

    int extra = rnd.next(3, 8);
    for (int i = 0; i < extra; ++i) {
        cases.push_back(rnd.next(0, 1) == 0 ? randomSmallCase() : randomStructuredCase());
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const Case& tc : cases) {
        println(tc.n, tc.k1, tc.alpha);
    }

    return 0;
}
