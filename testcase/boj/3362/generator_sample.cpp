#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    int n;
    int k;
    vector<int> a;
};

static Case makeNoOneCase() {
    int n = rnd.next(1, 12);
    int k = rnd.next(1, 60);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = rnd.next(2, 100);
    return {n, k, a};
}

static Case makeSingleOneCase() {
    int n = rnd.next(1, 12);
    int k = rnd.next(1, 80);
    vector<int> a(n);
    a[0] = 1;
    for (int i = 1; i < n; ++i) a[i] = rnd.next(2, 80);
    shuffle(a.begin(), a.end());
    return {n, k, a};
}

static Case makePrefixGrowthCase() {
    int n = rnd.next(4, 16);
    vector<int> usable;
    long long reach = 0;
    int targetPrefix = rnd.next(2, n);
    for (int i = 0; i < targetPrefix; ++i) {
        int upper = static_cast<int>(min<long long>(100000, reach + 1));
        int coin = rnd.next(1, max(1, upper));
        usable.push_back(coin);
        reach += coin;
    }

    vector<int> a = usable;
    while (static_cast<int>(a.size()) < n) {
        if (rnd.next(0, 1) == 0)
            a.push_back(rnd.next(1, 20));
        else
            a.push_back(rnd.next(static_cast<int>(min<long long>(100000, reach + 2)), 100000));
    }
    shuffle(a.begin(), a.end());

    int k;
    if (reach <= 1 || rnd.next(0, 2) == 0)
        k = rnd.next(1, static_cast<int>(min<long long>(1000000, reach)));
    else
        k = rnd.next(static_cast<int>(min<long long>(1000000, reach + 1)), 1000000);

    return {n, k, a};
}

static Case makeManySmallCase() {
    int n = rnd.next(8, 30);
    int maxCoin = rnd.next(1, 6);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = rnd.next(1, maxCoin);
    int k = rnd.next(1, min(1000000, n * maxCoin + rnd.next(0, 20)));
    return {n, k, a};
}

static Case makeBoundaryCase() {
    int n = rnd.next(1, 20);
    int k = rnd.any(vector<int>{1, 2, 999999, 1000000});
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 4) == 0)
            a[i] = 1;
        else
            a[i] = rnd.any(vector<int>{2, 3, 99999, 100000});
    }
    return {n, k, a};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    vector<Case> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        if (mode == 0)
            cases.push_back(makeNoOneCase());
        else if (mode == 1)
            cases.push_back(makeSingleOneCase());
        else if (mode == 2)
            cases.push_back(makePrefixGrowthCase());
        else if (mode == 3)
            cases.push_back(makeManySmallCase());
        else
            cases.push_back(makeBoundaryCase());
    }

    println(t);
    for (const Case& tc : cases) {
        println(tc.n, tc.k);
        println(tc.a);
    }

    return 0;
}
