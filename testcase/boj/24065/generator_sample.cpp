#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int targetSum = rnd.next(20, 220);
    int remaining = targetSum;
    vector<pair<int, int>> tests;

    while (remaining >= 2 && static_cast<int>(tests.size()) < 80) {
        int mode = rnd.next(0, 5);
        int n;

        if (mode <= 1) {
            n = rnd.next(2, min(8, remaining));
        } else if (mode == 2) {
            n = rnd.next(2, min(30, remaining));
        } else {
            n = rnd.next(2, min(120, remaining));
        }

        int maxA = (n - 1) * (n - 1) + 1;
        int a;

        if (mode == 0) {
            a = rnd.next(1, maxA);
        } else if (mode == 1) {
            a = rnd.any(vector<int>{1, maxA});
        } else if (mode == 2) {
            int side = rnd.next(1, n - 1);
            a = side * side;
            if (rnd.next(0, 1) && a < maxA) {
                ++a;
            }
        } else if (mode == 3) {
            int i = rnd.next(1, n - 1);
            int j = rnd.next(0, i);
            a = j * j + (i - j) * (i - j);
            a = max(1, min(a, maxA));
        } else {
            int nearTop = rnd.next(0, min(maxA - 1, max(3, n)));
            a = maxA - nearTop;
        }

        tests.push_back({n, a});
        remaining -= n;
    }

    println(static_cast<int>(tests.size()));
    for (const auto& test : tests) {
        println(test.first, test.second);
    }

    return 0;
}
