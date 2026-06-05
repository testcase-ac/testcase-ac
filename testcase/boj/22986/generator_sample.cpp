#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 60);
    vector<pair<long long, long long>> cases;
    cases.reserve(t);

    auto addCase = [&](long long n, long long k) {
        n = max(1LL, min(n, 1000000000LL));
        k = max(0LL, min(k, 1000000000LL));
        cases.emplace_back(n, k);
    };

    addCase(1, 0);
    addCase(1, rnd.next(0, 8));
    addCase(2, 0);
    addCase(2, 1);
    addCase(1000000000LL, 0);
    addCase(1000000000LL, 999999999LL);
    addCase(1000000000LL, 1000000000LL);

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 7);
        long long n, k;

        if (mode == 0) {
            n = rnd.next(1, 12);
            k = rnd.next(0, 12);
        } else if (mode == 1) {
            n = rnd.next(2, 50);
            k = rnd.next(0LL, n - 1);
        } else if (mode == 2) {
            n = rnd.next(2, 1000);
            k = max(0LL, n - 1 + rnd.next(-3, 3));
        } else if (mode == 3) {
            n = rnd.next(1, 1000000);
            k = rnd.any(vector<long long>{0, 1, 2, n / 2, max(0LL, n - 2), n - 1, n});
        } else if (mode == 4) {
            n = rnd.next(999999900LL, 1000000000LL);
            k = rnd.next(0LL, 1000000000LL);
        } else if (mode == 5) {
            n = rnd.next(1LL, 1000000000LL);
            k = rnd.next(max(0LL, n - 5), min(1000000000LL, n + 5));
        } else if (mode == 6) {
            n = rnd.next(1LL, 1000000000LL);
            k = rnd.wnext(1000000001, -3);
        } else {
            n = rnd.next(1LL, 1000000000LL);
            k = rnd.wnext(1000000001, 3);
        }

        addCase(n, k);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
