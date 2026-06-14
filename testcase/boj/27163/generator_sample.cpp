#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 80 : 18);
    long long aura = rnd.next(0, 40);
    int life = rnd.next(1, 35);

    if (mode == 1) {
        aura = rnd.next(0, 3);
        life = rnd.next(1, 8);
    } else if (mode == 2) {
        aura = rnd.next(20, 1000);
        life = rnd.next(1, 12);
    } else if (mode == 4) {
        aura = rnd.next(0, 1000000000);
        life = rnd.next(1, 5000);
        n = rnd.next(1, 12);
    } else if (mode == 5) {
        aura = rnd.next(0, 150);
        life = rnd.next(1, 120);
    }

    vector<pair<long long, int>> attacks;
    attacks.reserve(n);

    for (int i = 0; i < n; ++i) {
        int kind = rnd.next(0, 99);
        long long x;
        int y;

        if (kind < 18) {
            x = -1;
            y = rnd.next(0, mode == 4 ? 5000 : max(10, life + 5));
        } else if (kind < 36) {
            x = rnd.next(0LL, mode == 4 ? 1000000000LL : max(50LL, aura + 20));
            y = -1;
        } else {
            if (mode == 1 && rnd.next(0, 1) == 0) {
                x = aura + rnd.next(1, 8);
            } else if (mode == 2 && rnd.next(0, 2) > 0) {
                x = rnd.next(0LL, aura);
            } else if (mode == 4 && rnd.next(0, 3) == 0) {
                x = rnd.next(900000000LL, 1000000000LL);
            } else {
                x = rnd.next(0LL, max(20LL, aura + 10));
            }

            if (mode == 3 && rnd.next(0, 3) == 0) {
                y = 0;
            } else if (mode == 1 && rnd.next(0, 2) > 0) {
                y = rnd.next(life, min(5000, life + 10));
            } else {
                y = rnd.next(0, mode == 4 ? 5000 : max(10, life + 5));
            }
        }

        attacks.emplace_back(x, y);
    }

    if (mode == 3 && n >= 3) {
        attacks[0] = {0, rnd.next(0, 3)};
        attacks[1] = {rnd.next(0, 3), 0};
        attacks[2] = {0, -1};
    }

    println(n, aura, life);
    for (auto [x, y] : attacks) {
        println(x, y);
    }

    return 0;
}
