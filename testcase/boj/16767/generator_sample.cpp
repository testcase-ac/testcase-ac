#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 80 : 18);
    vector<pair<long long, int>> cows;
    cows.reserve(n);

    if (mode == 0) {
        long long arrive = rnd.next(1LL, 100LL);
        for (int i = 0; i < n; ++i) {
            cows.emplace_back(arrive, rnd.next(1, 40));
        }
    } else if (mode == 1) {
        long long arrive = rnd.next(1LL, 30LL);
        int longEat = rnd.next(40, 150);
        cows.emplace_back(arrive, longEat);
        for (int i = 1; i < n; ++i) {
            cows.emplace_back(arrive + rnd.next(0LL, (long long)longEat), rnd.next(1, 25));
        }
    } else if (mode == 2) {
        long long now = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            now += rnd.next(2LL, 30LL);
            cows.emplace_back(now, rnd.next(1, 20));
        }
    } else if (mode == 3) {
        long long now = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            int eat = rnd.next(1, 30);
            cows.emplace_back(now, eat);
            now += eat;
            if (rnd.next(0, 3) == 0) now += rnd.next(1LL, 8LL);
        }
    } else if (mode == 4) {
        long long base = rnd.next(999999000LL, 1000000000LL - n);
        for (int i = 0; i < n; ++i) {
            cows.emplace_back(base + rnd.next(0LL, 30LL), rnd.next(9000, 10000));
        }
    } else {
        long long now = rnd.next(1LL, 200LL);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) now += rnd.next(20LL, 200LL);
            cows.emplace_back(now + rnd.next(0LL, 20LL), rnd.next(1, 10000));
            if (rnd.next(0, 2) == 0) now += rnd.next(0LL, 10LL);
        }
    }

    shuffle(cows.begin(), cows.end());

    println(n);
    for (auto [a, t] : cows) {
        println(a, t);
    }

    return 0;
}
