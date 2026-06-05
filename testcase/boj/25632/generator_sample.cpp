#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> intervalAround(int center, int radius) {
    int lo = max(2, center - rnd.next(0, radius));
    int hi = min(1000, center + rnd.next(0, radius));
    if (lo > hi) swap(lo, hi);
    return {lo, hi};
}

pair<int, int> randomInterval(int loLimit = 2, int hiLimit = 1000) {
    int lo = rnd.next(loLimit, hiLimit);
    int hi = rnd.next(lo, hiLimit);
    return {lo, hi};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes;
    vector<bool> composite(1001, false);
    for (int i = 2; i <= 1000; ++i) {
        if (!composite[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= 1000; j += i) composite[j] = true;
        }
    }

    pair<int, int> first;
    pair<int, int> second;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        int split = rnd.next(2, 999);
        first = randomInterval(2, split);
        second = randomInterval(split + 1, 1000);
        if (rnd.next(0, 1)) swap(first, second);
    } else if (mode == 1) {
        int lo = rnd.next(2, 900);
        int hi = rnd.next(lo, 1000);
        first = {lo, hi};
        second = {rnd.next(lo, hi), rnd.next(lo, hi)};
        if (second.first > second.second) swap(second.first, second.second);
        if (rnd.next(0, 1)) swap(first, second);
    } else if (mode == 2) {
        int lo = rnd.next(2, 1000);
        int hi = rnd.next(lo, 1000);
        first = {lo, hi};
        second = first;
    } else if (mode == 3) {
        int left = rnd.next(2, 980);
        int right = rnd.next(left, min(1000, left + 40));
        int overlapLo = rnd.next(left, right);
        int overlapHi = rnd.next(overlapLo, min(1000, right + 40));
        first = {left, right};
        second = {overlapLo, overlapHi};
    } else if (mode == 4) {
        vector<pair<int, int>> choices = {
            {2, rnd.next(2, 20)},
            {rnd.next(980, 1000), 1000},
            {2, 1000},
            {rnd.next(2, 10), rnd.next(990, 1000)}
        };
        first = rnd.any(choices);
        second = rnd.any(choices);
    } else {
        int p = rnd.any(primes);
        int q = rnd.any(primes);
        first = intervalAround(p, rnd.next(0, 60));
        second = intervalAround(q, rnd.next(0, 60));
    }

    println(first.first, first.second);
    println(second.first, second.second);
    return 0;
}
