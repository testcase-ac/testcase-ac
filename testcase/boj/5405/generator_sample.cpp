#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

long long houseCount(int n) {
    return 1LL << (2 * n);
}

long long clampHouse(long long x, long long maxHouse) {
    return max(1LL, min(x, maxHouse));
}

pair<long long, long long> randomPair(int n) {
    long long maxHouse = houseCount(n);
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        long long h = rnd.next(1LL, maxHouse);
        return {h, h};
    }
    if (mode == 1) {
        long long h = rnd.next(1LL, maxHouse - 1);
        return {h, h + 1};
    }
    if (mode == 2) {
        long long block = houseCount(max(1, n - 1));
        long long edge = rnd.next(1, 3) * block;
        return {clampHouse(edge, maxHouse), clampHouse(edge + rnd.next(-2, 2), maxHouse)};
    }
    if (mode == 3) {
        return {rnd.next(1LL, min(16LL, maxHouse)), rnd.next(max(1LL, maxHouse - 15), maxHouse)};
    }

    return {rnd.next(1LL, maxHouse), rnd.next(1LL, maxHouse)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int, long long, long long>> cases;
    cases.emplace_back(1, 1, 1);
    cases.emplace_back(1, rnd.next(1, 4), rnd.next(1, 4));
    cases.emplace_back(2, 1, 16);
    cases.emplace_back(3, rnd.next(1, 64), rnd.next(1, 64));
    cases.emplace_back(15, 1, houseCount(15));
    cases.emplace_back(15, houseCount(15), rnd.next(houseCount(15) - 1024, houseCount(15)));

    int extra = rnd.next(6, 14);
    for (int i = 0; i < extra; ++i) {
        int n;
        if (rnd.next(0, 4) == 0) {
            n = rnd.next(12, 15);
        } else {
            n = rnd.next(1, 8);
        }

        auto [h, o] = randomPair(n);
        cases.emplace_back(n, h, o);
    }

    shuffle(cases.begin(), cases.end());

    println(cases.size());
    for (auto [n, h, o] : cases) {
        println(n, h, o);
    }

    return 0;
}
