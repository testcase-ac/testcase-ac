#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int, int, int>> cases;

    int smallR = rnd.next(1, 12);
    cases.emplace_back(smallR, smallR, rnd.any(vector<int>{0, 1, 50, 100}));

    int nearR = rnd.next(1, 200);
    cases.emplace_back(nearR, nearR + rnd.next(0, 5), rnd.next(0, 100));

    int largeR = rnd.next(800, 1000);
    cases.emplace_back(largeR, rnd.next(largeR, 10000), rnd.any(vector<int>{0, 25, 75, 100}));

    int maxR = 1000;
    cases.emplace_back(maxR, rnd.any(vector<int>{1000, 1001, 5000, 10000}), rnd.next(0, 100));

    int extraCases = rnd.next(2, 5);
    for (int i = 0; i < extraCases; ++i) {
        int r = rnd.next(1, 1000);
        int mode = rnd.next(4);
        int h;
        if (mode == 0) {
            h = r;
        } else if (mode == 1) {
            h = min(10000, r + rnd.next(1, 20));
        } else if (mode == 2) {
            h = rnd.next(r, min(10000, r + 1000));
        } else {
            h = rnd.next(r, 10000);
        }
        int s = rnd.next(0, 100);
        cases.emplace_back(r, h, s);
    }

    shuffle(cases.begin(), cases.end());

    for (const auto& [r, h, s] : cases) {
        println(r, h, s);
    }
    println(0, 0, 0);

    return 0;
}
