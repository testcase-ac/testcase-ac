#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    for (int n = 2; n <= 7; ++n) {
        int maxSum = 9 * n;
        cases.push_back({n, 0});
        cases.push_back({n, maxSum});
        cases.push_back({n, rnd.next(0, maxSum)});
        cases.push_back({n, rnd.next(max(0, maxSum - 3), maxSum)});
        cases.push_back({n, maxSum + rnd.next(1, 20)});
    }

    int extraCases = rnd.next(4, 12);
    for (int i = 0; i < extraCases; ++i) {
        int n = rnd.next(2, 7);
        int mode = rnd.next(0, 4);
        int s;

        if (mode == 0) {
            s = rnd.next(0, 9 * n);
        } else if (mode == 1) {
            s = rnd.next(0, min(5, 9 * n));
        } else if (mode == 2) {
            s = rnd.next(max(0, 9 * n - 5), 9 * n);
        } else if (mode == 3) {
            s = 9 * n + rnd.next(1, 100);
        } else {
            s = rnd.next(100000, 1000000000);
        }

        cases.push_back({n, s});
    }

    shuffle(cases.begin(), cases.end());

    int keep = rnd.next(8, (int)cases.size());
    for (int i = 0; i < keep; ++i) {
        println(cases[i].first, cases[i].second);
    }

    return 0;
}
