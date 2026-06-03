#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    cases.push_back({1, 1});

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        int z = rnd.next(1, 10);
        for (int i = 0; i < z; ++i) {
            int w = rnd.next(1, 8);
            int k = rnd.next(1, 8);
            cases.push_back({w, k});
        }
    } else if (mode == 1) {
        int z = rnd.next(4, 10);
        for (int i = 0; i < z; ++i) {
            int longSide = rnd.next(1, 1000);
            if (rnd.next(0, 1)) {
                cases.push_back({1, longSide});
            } else {
                cases.push_back({longSide, 1});
            }
        }
    } else if (mode == 2) {
        int z = rnd.next(4, 10);
        for (int i = 0; i < z; ++i) {
            int w = rnd.next(2, 30);
            int k = rnd.next(2, 30);
            if (rnd.next(0, 1)) w = 2 * rnd.next(1, 15);
            if (rnd.next(0, 1)) k = 2 * rnd.next(1, 15) - 1;
            cases.push_back({w, k});
        }
    } else if (mode == 3) {
        cases.push_back({1000, 1000});
        cases.push_back({1, 1000});
        cases.push_back({1000, 1});
        cases.push_back({999, 1000});
        cases.push_back({1000, 999});
        int z = rnd.next(0, 5);
        for (int i = 0; i < z; ++i) cases.push_back({rnd.next(900, 1000), rnd.next(900, 1000)});
    } else if (mode == 4) {
        int z = rnd.next(5, 10);
        for (int i = 0; i < z; ++i) {
            int side = rnd.next(1, 1000);
            cases.push_back({side, side});
        }
    } else {
        int z = rnd.next(5, 10);
        for (int i = 0; i < z; ++i) {
            int small = rnd.next(2, 20);
            int large = rnd.next(50, 1000);
            if (rnd.next(0, 1)) {
                cases.push_back({small, large});
            } else {
                cases.push_back({large, small});
            }
        }
    }

    shuffle(cases.begin(), cases.end());
    if (cases.size() > 10) cases.resize(10);

    println((int)cases.size());
    for (const auto& tc : cases) println(tc.first, tc.second);
    return 0;
}
