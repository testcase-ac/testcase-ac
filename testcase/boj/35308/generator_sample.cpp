#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 18);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    int remainingN = 180;
    for (int i = 0; i < t; ++i) {
        int slotsLeft = t - i;
        int maxN = remainingN - (slotsLeft - 1);
        int n;
        if (i == 0 && rnd.next(3) == 0) {
            n = 1;
        } else if (maxN >= 20 && rnd.next(4) == 0) {
            n = rnd.next(20, min(maxN, 80));
        } else {
            n = rnd.next(1, min(maxN, 20));
        }
        remainingN -= n;

        int mode = rnd.next(5);
        int k;
        if (n == 1) {
            k = 1;
        } else if (mode <= 1) {
            k = 2;
        } else if (mode == 2) {
            k = 1;
        } else if (mode == 3) {
            k = n;
        } else if (n == 2) {
            k = 1;
        } else {
            k = rnd.next(3, n);
        }
        cases.emplace_back(n, k);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
