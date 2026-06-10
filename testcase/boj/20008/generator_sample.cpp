#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 5);
    int hp;

    if (mode == 0) {
        hp = rnd.next(1, 30);
    } else if (mode == 1) {
        hp = rnd.next(90000, 100000);
    } else {
        hp = rnd.next(20, 5000);
    }

    int minDamage = (hp + 9) / 10;
    while (n * minDamage >= hp) {
        if (n > 1) {
            --n;
        } else {
            ++hp;
        }
        minDamage = (hp + 9) / 10;
    }

    vector<int> damages(n, minDamage);
    int spare = hp - 1 - n * minDamage;

    if (mode == 2) {
        while (spare > 0) {
            int i = rnd.next(n);
            int add = rnd.next(1, spare);
            damages[i] += add;
            spare -= add;
        }
    } else if (mode == 3) {
        int addEach = n == 0 ? 0 : rnd.next(0, spare / n);
        for (int& damage : damages) damage += addEach;
        spare -= addEach * n;
        for (int i = 0; i < n && spare > 0; ++i) {
            int add = rnd.next(0, spare);
            damages[i] += add;
            spare -= add;
        }
    } else {
        for (int& damage : damages) {
            if (spare == 0) break;
            int add = rnd.next(0, spare);
            damage += add;
            spare -= add;
        }
    }

    vector<int> cooldowns(10);
    iota(cooldowns.begin(), cooldowns.end(), 1);
    if (mode == 4) {
        reverse(cooldowns.begin(), cooldowns.end());
    } else {
        shuffle(cooldowns.begin(), cooldowns.end());
    }
    cooldowns.resize(n);

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    if (mode != 5) shuffle(order.begin(), order.end());

    println(n, hp);
    for (int idx : order) {
        println(cooldowns[idx], damages[idx]);
    }

    return 0;
}
