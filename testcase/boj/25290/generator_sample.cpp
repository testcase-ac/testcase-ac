#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

long long oddN(long long lo, long long hi) {
    long long n = rnd.next(lo, hi);
    if (n % 2 == 0) {
        if (n == hi) --n;
        else ++n;
    }
    return n;
}

long long validK(long long n, long long k) {
    long long maxK = n * n - 2;
    return max(1LL, min(k, maxK));
}

pair<long long, long long> makeCase(int mode) {
    long long n;
    switch (mode) {
        case 0:
            n = rnd.any(vector<long long>{3, 5, 7, 9});
            return {n, rnd.next(1LL, n * n - 2)};
        case 1:
            n = oddN(11, 39);
            return {n, rnd.any(vector<long long>{1, n - 2, n - 1, n, n + 1})};
        case 2:
            n = oddN(41, 301);
            return {n, validK(n, rnd.next(1LL, 2 * n + 15))};
        case 3:
            n = oddN(101, 999);
            return {n, validK(n, n * n - 2 - rnd.next(0LL, 30LL))};
        case 4:
            n = oddN(3, 9999);
            return {n, validK(n, rnd.next(1LL, n * n - 2))};
        default:
            n = rnd.any(vector<long long>{9991, 9993, 9995, 9997, 9999});
            return {n, validK(n, rnd.any(vector<long long>{n - 1, n, n + 1, n * n / 2, n * n - 2}))};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, long long>> cases;
    cases.push_back({3, 1});
    cases.push_back({5, 3});
    cases.push_back({5, 4});
    cases.push_back({5, 12});
    cases.push_back({9999, 9999LL * 9999 - 2});

    int randomCases = rnd.next(8, 20);
    for (int i = 0; i < randomCases; ++i) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const auto& [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
