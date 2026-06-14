#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<pair<int, int>> cows;

    if (mode == 0) {
        int maxWeight = rnd.next(2, 30);
        int maxStrength = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            cows.push_back({rnd.next(1, maxWeight), rnd.next(1, maxStrength)});
        }
    } else if (mode == 1) {
        int target = rnd.next(20, 200);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, min(10000, target - 1));
            int s = target - w;
            cows.push_back({w, max(1, s)});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) {
            int w = (i % 2 == 0) ? rnd.next(9000, 10000) : rnd.next(1, 20);
            int s = (i % 3 == 0) ? rnd.next(1, 50) : rnd.next(999999900, 1000000000);
            cows.push_back({w, s});
        }
    } else if (mode == 3) {
        int baseWeight = rnd.next(1, 10000);
        int baseStrength = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(max(1, baseWeight - 5), min(10000, baseWeight + 5));
            int s = rnd.next(max(1, baseStrength - 100), min(1000000000, baseStrength + 100));
            cows.push_back({w, s});
        }
    } else if (mode == 4) {
        n = rnd.next(10, 25);
        int strength = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            cows.push_back({rnd.next(1, 10000), strength});
        }
    } else {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 10000);
            long long scaled = 1LL * w * rnd.next(1, 100);
            int s = static_cast<int>(min(1000000000LL, max(1LL, scaled + rnd.next(-50, 50))));
            cows.push_back({w, s});
        }
    }

    shuffle(cows.begin(), cows.end());

    println(static_cast<int>(cows.size()));
    for (const auto& cow : cows) {
        println(cow.first, cow.second);
    }

    return 0;
}
