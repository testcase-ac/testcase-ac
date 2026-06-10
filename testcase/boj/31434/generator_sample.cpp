#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int k = 1;
    vector<pair<int, int>> effects;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 100);
        int a = rnd.any(vector<int>{1, 2, 3, 10, 25, 50});
        int b = rnd.next(1, 50);
        effects.push_back({a, b});
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        k = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            effects.push_back({rnd.next(1, 12), rnd.next(1, 12)});
        }
    } else if (mode == 2) {
        n = rnd.next(5, 14);
        k = rnd.next(15, 45);
        int baseCost = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int a = min(50, baseCost + rnd.next(0, 18));
            int b = rnd.next(1, 50);
            effects.push_back({a, b});
        }
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        k = rnd.next(20, 100);
        int cheapGain = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            if (i < n / 2) {
                effects.push_back({rnd.next(1, 5), rnd.next(cheapGain, min(50, cheapGain + 4))});
            } else {
                effects.push_back({rnd.next(35, 50), rnd.next(25, 50)});
            }
        }
    } else if (mode == 4) {
        n = rnd.next(8, 25);
        k = rnd.next(30, 100);
        vector<pair<int, int>> palette = {
            {1, 1},
            {2, 3},
            {5, 8},
            {13, 21},
            {50, 50},
        };
        for (int i = 0; i < n; ++i) {
            effects.push_back(rnd.any(palette));
        }
    } else {
        n = rnd.next(20, 60);
        k = rnd.next(60, 100);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 50);
            int b = rnd.next(1, 50);
            if (rnd.next(0, 3) == 0) {
                a = rnd.any(vector<int>{1, 50});
            }
            if (rnd.next(0, 3) == 0) {
                b = rnd.any(vector<int>{1, 50});
            }
            effects.push_back({a, b});
        }
    }

    shuffle(effects.begin(), effects.end());

    println(n, k);
    for (auto [a, b] : effects) {
        println(a, b);
    }

    return 0;
}
