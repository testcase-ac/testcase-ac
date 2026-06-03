#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int targetCases = rnd.next(4, 14);
    int modeCount = rnd.next(2, 5);

    for (int mode = 0; mode < modeCount && (int)cases.size() < targetCases; ++mode) {
        if (mode == 0) {
            int total = 13;
            int x = rnd.next(0, total);
            cases.emplace_back(x, total - x);
        } else if (mode == 1) {
            int value = rnd.next(1, 60);
            cases.emplace_back(value, value);
        } else if (mode == 2) {
            int high = rnd.next(2, 80);
            int low = rnd.next(0, high - 1);
            if (rnd.next(2) == 0) {
                cases.emplace_back(high, low);
            } else {
                cases.emplace_back(low, high);
            }
        } else if (mode == 3) {
            if (rnd.next(2) == 0) {
                cases.emplace_back(rnd.next(1, 1000), 0);
            } else {
                cases.emplace_back(0, rnd.next(1, 1000));
            }
        } else {
            int x = rnd.next(0, 1000);
            int y = rnd.next(0, 1000);
            if (x == 0 && y == 0) {
                x = 1;
            }
            cases.emplace_back(x, y);
        }
    }

    while ((int)cases.size() < targetCases) {
        int x = rnd.next(0, 1000);
        int y = rnd.next(0, 1000);
        if (x == 0 && y == 0) {
            x = 1;
        }
        cases.emplace_back(x, y);
    }

    shuffle(cases.begin(), cases.end());

    for (const auto& testCase : cases) {
        println(testCase.first, testCase.second);
    }
    println(0, 0);

    return 0;
}
