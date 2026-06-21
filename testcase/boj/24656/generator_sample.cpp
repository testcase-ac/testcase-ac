#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedA(long long value) {
    return (int)max(1LL, min(1000000000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> piles;

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 30 : 18);

    for (int i = 0; i < n; ++i) {
        int kind = rnd.next(0, 6);
        int a;
        int b;

        if (kind == 0) {
            b = 1;
            a = rnd.next(1, 40);
        } else if (kind == 1) {
            b = 2 * rnd.next(1, 20);
            int rem = rnd.next(0, b);
            a = boundedA((long long)rnd.next(0, 8) * (b + 1LL) + rem);
        } else if (kind == 2) {
            b = 2 * rnd.next(1, 20) + 1;
            a = rnd.next(1, 300);
        } else if (kind == 3) {
            b = rnd.next(2, 60);
            int rem = rnd.any(vector<int>{0, 1, b - 1, b});
            a = boundedA((long long)rnd.next(0, 12) * (b + 1LL) + rem);
        } else if (kind == 4) {
            b = rnd.next(2, 1000000000);
            a = rnd.next(1, min(1000000000, b + rnd.next(0, 7)));
        } else {
            b = rnd.any(vector<int>{1, 2, 3, 4, 999999937, 1000000000});
            a = rnd.any(vector<int>{1, 2, 3, 4, 999999999, 1000000000});
        }

        piles.push_back({a, b});
    }

    if (mode == 0 && !piles.empty()) {
        piles[0] = {1, 1};
    } else if (mode == 1 && piles.size() >= 2) {
        piles[0] = {1000000000, 1};
        piles[1] = {1, 1000000000};
    } else if (mode == 2) {
        for (auto& pile : piles) {
            pile.second = 2 * rnd.next(1, 15);
            pile.first = boundedA((long long)rnd.next(0, 10) * (pile.second + 1LL) + pile.second);
        }
    }

    shuffle(piles.begin(), piles.end());

    println((int)piles.size());
    for (const auto& pile : piles) {
        println(pile.first, pile.second);
    }

    return 0;
}
