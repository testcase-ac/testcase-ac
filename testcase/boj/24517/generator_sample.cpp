#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(12, 40);
    vector<pair<long long, int>> cases;

    for (int k = 1; k <= 10 && (int)cases.size() < q; ++k) {
        long long cycle = 1LL * k * (k + 1) / 2;
        long long diff;
        if (rnd.next(2) == 0) {
            diff = rnd.next(1LL, cycle);
        } else {
            long long multiplier = rnd.next(1LL, 1000000000LL / cycle);
            long long offset = rnd.next(-2LL, 2LL);
            diff = max(1LL, min(999999999LL, multiplier * cycle + offset));
        }
        cases.push_back({diff, k});
    }

    while ((int)cases.size() < q) {
        int k = rnd.next(1, 10);
        int mode = rnd.next(5);
        long long cycle = 1LL * k * (k + 1) / 2;
        long long diff;

        if (mode == 0) {
            diff = rnd.next(1LL, min(30LL, 999999999LL));
        } else if (mode == 1) {
            diff = rnd.next(1LL, cycle);
        } else if (mode == 2) {
            long long multiplier = rnd.next(1LL, 1000000000LL / cycle);
            long long offset = rnd.next(-cycle, cycle);
            diff = max(1LL, min(999999999LL, multiplier * cycle + offset));
        } else if (mode == 3) {
            diff = rnd.next(999999900LL, 999999999LL);
        } else {
            diff = rnd.next(1LL, 999999999LL);
        }

        cases.push_back({diff, k});
    }

    shuffle(cases.begin(), cases.end());

    println(q);
    for (auto [diff, k] : cases) {
        long long maxA = 1000000000LL - diff;
        long long a;
        if (rnd.next(4) == 0) {
            a = maxA;
        } else if (rnd.next(3) == 0) {
            a = rnd.next(1LL, min(maxA, 30LL));
        } else {
            a = rnd.next(1LL, maxA);
        }
        println(a, a + diff, k);
    }

    return 0;
}
