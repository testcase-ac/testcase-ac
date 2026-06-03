#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> boundaryScores = {0, 1, 9, 10};
    int testCases = rnd.next(1, 40);
    vector<pair<int, int>> cases;
    cases.reserve(testCases);

    for (int i = 0; i < testCases; ++i) {
        int mode = rnd.next(0, 5);
        int a = 0;
        int b = 0;

        if (mode == 0) {
            a = rnd.next(0, 10);
            b = 0;
        } else if (mode == 1) {
            a = 0;
            b = rnd.next(0, 10);
        } else if (mode == 2) {
            a = rnd.next(0, 10);
            b = a;
        } else if (mode == 3) {
            a = rnd.any(boundaryScores);
            b = rnd.any(boundaryScores);
        } else if (mode == 4) {
            int sum = rnd.next(0, 20);
            int lo = max(0, sum - 10);
            int hi = min(10, sum);
            a = rnd.next(lo, hi);
            b = sum - a;
        } else {
            a = rnd.next(0, 10);
            b = rnd.next(0, 10);
        }

        cases.emplace_back(a, b);
    }

    for (auto [a, b] : cases) {
        int spaces = rnd.next(1, 4);
        printf("%d%*s%d\n", a, spaces, "", b);
    }
    println(-1, -1);

    return 0;
}
