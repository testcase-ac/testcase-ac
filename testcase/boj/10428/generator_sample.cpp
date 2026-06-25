#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int clampN(long long n) {
    if (n < 1) return 1;
    if (n > 1000000) return 1000000;
    return static_cast<int>(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int targetT = rnd.next(20, 100);
    vector<pair<int, int>> cases;
    set<pair<int, int>> seen;

    auto addCase = [&](int n, int e) {
        n = clampN(n);
        e = max(1, min(10, e));
        pair<int, int> cur = {n, e};
        if (seen.insert(cur).second) cases.push_back(cur);
    };

    addCase(1, rnd.next(1, 10));
    addCase(1000000, rnd.next(1, 10));
    addCase(rnd.next(1, 10), 1);
    addCase(rnd.next(1, 100), 10);

    while (static_cast<int>(cases.size()) < targetT) {
        int mode = rnd.next(6);
        int e = rnd.next(1, 10);

        if (mode == 0) {
            addCase(rnd.next(1, 30), e);
        } else if (mode == 1) {
            addCase(rnd.next(999900, 1000000), e);
        } else if (mode == 2) {
            addCase(rnd.next(1, 1000000), e);
        } else {
            int base = e + 1;
            long long value = 1;
            int exponent = rnd.next(0, 16);
            for (int i = 0; i < exponent && value <= 1000000; ++i) {
                value *= base;
            }

            int deltaLimit = (mode == 3 ? 1 : rnd.next(2, 50));
            int delta = rnd.next(-deltaLimit, deltaLimit);
            addCase(clampN(value + delta), e);
        }
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const auto& [n, e] : cases) {
        println(n, e);
    }

    return 0;
}
