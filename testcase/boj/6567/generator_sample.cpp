#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> candidates;

    for (int c = 1; c <= 32; ++c) {
        for (int s = 1; s <= 32; ++s) {
            if (c * s <= 32) {
                candidates.push_back({c, s});
            }
        }
    }

    vector<pair<int, int>> cases;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int c = rnd.next(1, 32);
        cases.push_back({c, 1});
        cases.push_back({1, rnd.next(1, 32)});
        cases.push_back({rnd.next(2, 32), 1});
    } else if (mode == 1) {
        int product = rnd.next(1, 32);
        vector<pair<int, int>> factors;
        for (int c = 1; c <= product; ++c) {
            if (product % c == 0) {
                factors.push_back({c, product / c});
            }
        }
        shuffle(factors.begin(), factors.end());
        int take = rnd.next(1, min<int>(5, factors.size()));
        cases.insert(cases.end(), factors.begin(), factors.begin() + take);
    } else if (mode == 2) {
        int s = rnd.next(2, 32);
        int maxColors = 32 / s;
        cases.push_back({rnd.next(1, maxColors), s});
        cases.push_back({maxColors, s});
    } else {
        int count = rnd.next(3, 8);
        shuffle(candidates.begin(), candidates.end());
        cases.insert(cases.end(), candidates.begin(), candidates.begin() + count);
    }

    while ((int)cases.size() < rnd.next(4, 9)) {
        cases.push_back(rnd.any(candidates));
    }

    for (auto [c, s] : cases) {
        println(c, s);
    }
    println(0, 0);

    return 0;
}
