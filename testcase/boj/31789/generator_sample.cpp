#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;
    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(60, 100) : rnd.next(1, 12));
    long long x = 1, s = 1;
    vector<pair<long long, long long>> weapons;

    if (mode == 4 || mode == 5) {
        x = rnd.next(LIM - 20, LIM);
        s = rnd.next(LIM - 20, LIM);
    } else {
        x = rnd.next(1, 30);
        s = rnd.next(1, 30);
    }

    weapons.reserve(n);
    for (int i = 0; i < n; ++i) {
        long long c, p;
        if (mode == 4 || mode == 5) {
            c = rnd.next(max(1LL, x - 30), LIM);
            p = rnd.next(max(1LL, s - 30), LIM);
        } else {
            c = rnd.next(1, 35);
            p = rnd.next(1, 35);
        }
        weapons.emplace_back(c, p);
    }

    int special = rnd.next(0, n - 1);
    if (mode == 0) {
        weapons[special] = {rnd.next(1LL, x), rnd.next(s + 1, min(LIM, s + 20))};
    } else if (mode == 1) {
        weapons[special] = {rnd.next(1LL, x), s};
    } else if (mode == 2) {
        weapons[special] = {min(LIM, x + rnd.next(1, 20)), min(LIM, s + rnd.next(1, 20))};
    } else if (mode == 3) {
        weapons[special] = {x, min(LIM, s + rnd.next(1, 20))};
    } else if (mode == 4) {
        weapons[special] = {x, s};
    } else {
        weapons[special] = {rnd.next(1LL, x), LIM};
    }

    if (mode == 1 || mode == 2 || mode == 4) {
        for (auto& weapon : weapons) {
            if (weapon.first <= x) {
                weapon.second = rnd.next(1LL, s);
            }
        }
    }

    shuffle(weapons.begin(), weapons.end());

    println(n);
    println(x, s);
    for (auto [c, p] : weapons) {
        println(c, p);
    }

    return 0;
}
