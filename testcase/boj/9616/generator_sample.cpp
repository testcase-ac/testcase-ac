#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(6, 12);
    vector<pair<int, int>> cases;
    cases.reserve(caseCount);

    auto addCase = [&](int m, int n) {
        cases.push_back({m, n});
    };

    addCase(rnd.next(1, 5), rnd.next(1, 5));

    for (int i = 1; i < caseCount; ++i) {
        int mode = rnd.next(0, 6);

        if (mode == 0) {
            int side = rnd.next(1, 30);
            addCase(side, side);
        } else if (mode == 1) {
            int longSide = rnd.next(20, 1000);
            if (rnd.next(0, 1) == 0) {
                addCase(1, longSide);
            } else {
                addCase(longSide, 1);
            }
        } else if (mode == 2) {
            addCase(rnd.next(2, 40), rnd.next(2, 40));
        } else if (mode == 3) {
            addCase(rnd.next(99950, 100000), rnd.next(1, 75));
        } else if (mode == 4) {
            int a = rnd.next(1, 100000);
            int b = rnd.next(1, 100000);
            if (rnd.next(0, 1) == 0) {
                addCase(a, b);
            } else {
                addCase(b, a);
            }
        } else {
            int oddSide = 2 * rnd.next(0, 250) + 1;
            int evenSide = 2 * rnd.next(1, 250);
            if (rnd.next(0, 1) == 0) {
                addCase(oddSide, evenSide);
            } else {
                addCase(evenSide, oddSide);
            }
        }
    }

    for (auto [m, n] : cases) {
        println(m, n);
    }
    println(0, 0);

    return 0;
}
