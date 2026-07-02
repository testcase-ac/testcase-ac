#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int maxInversions(int n) {
    return n * (n - 1) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(4, 8);
    vector<pair<int, int>> cases;
    cases.reserve(caseCount);

    for (int i = 0; i < caseCount; ++i) {
        int mode = rnd.next(0, 5);
        int n;
        int k;

        if (mode == 0) {
            n = rnd.next(1, 5);
            k = rnd.next(0, min(200, maxInversions(n)));
        } else if (mode == 1) {
            n = rnd.next(1, 18);
            k = 0;
        } else if (mode == 2) {
            n = rnd.next(2, 18);
            k = min(200, maxInversions(n));
        } else if (mode == 3) {
            n = rnd.next(1, 18);
            int lo = min(180, maxInversions(n) + 1);
            k = rnd.next(lo, 200);
        } else if (mode == 4) {
            n = rnd.next(14, 18);
            k = rnd.next(0, 200);
        } else {
            n = rnd.next(6, 13);
            int pivot = min(200, maxInversions(n));
            k = rnd.next(max(0, pivot - 10), min(200, pivot + 10));
        }

        cases.push_back({n, k});
    }

    shuffle(cases.begin(), cases.end());

    for (const auto& test : cases) {
        println(test.first, test.second);
    }
    println(0, 0);

    return 0;
}
