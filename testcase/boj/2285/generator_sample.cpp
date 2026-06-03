#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    vector<pair<long long, long long>> villages;

    auto addVillage = [&](long long x, long long a) {
        villages.push_back({x, a});
    };

    if (mode == 0) {
        n = 1;
        addVillage(rnd.next(-1000000000LL, 1000000000LL), rnd.next(1LL, 1000000000LL));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        long long x = rnd.next(-20LL, 20LL);
        int positiveAt = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            long long population = (i == positiveAt) ? rnd.next(1LL, 30LL) : rnd.next(0LL, 30LL);
            addVillage(x, population);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        long long base = rnd.next(-30LL, 10LL);
        long long step = rnd.next(1LL, 9LL);
        for (int i = 0; i < n; ++i) {
            long long population = (i % 2 == 0) ? rnd.next(0LL, 5LL) : rnd.next(1LL, 20LL);
            addVillage(base + step * i, population);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(-100LL, 100LL);
            long long population = rnd.wnext(101, -2);
            addVillage(x, population);
        }
        villages[rnd.next(0, n - 1)].second = rnd.next(1LL, 100LL);
    } else if (mode == 4) {
        n = rnd.next(4, 10);
        addVillage(-1000000000LL, rnd.next(0LL, 20LL));
        addVillage(1000000000LL, rnd.next(0LL, 20LL));
        for (int i = 2; i < n; ++i) {
            addVillage(rnd.next(-1000000000LL, 1000000000LL), rnd.next(0LL, 50LL));
        }
        villages[rnd.next(0, n - 1)].second = rnd.next(1LL, 100LL);
    } else {
        n = rnd.next(2, 16);
        long long left = rnd.next(-1000LL, -1LL);
        long long right = rnd.next(0LL, 1000LL);
        long long weight = rnd.next(1LL, 50LL);
        addVillage(left, weight);
        addVillage(right, weight);
        for (int i = 2; i < n; ++i) {
            addVillage(rnd.next(left, right), rnd.next(0LL, 10LL));
        }
    }

    long long totalPopulation = 0;
    for (const auto& village : villages) totalPopulation += village.second;
    if (totalPopulation == 0) villages[rnd.next(0, (int)villages.size() - 1)].second = 1;

    shuffle(villages.begin(), villages.end());

    println((int)villages.size());
    for (const auto& village : villages) println(village.first, village.second);

    return 0;
}
