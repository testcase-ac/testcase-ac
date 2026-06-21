#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = rnd.next(2, 3);
    } else if (mode == 2) {
        k = rnd.next(4, 6);
    } else if (mode == 3) {
        k = rnd.next(2, 8);
    } else {
        k = rnd.next(1, 10);
    }

    int n = 1 << k;
    vector<int> skills(n);
    for (int i = 0; i < n; ++i) {
        skills[i] = i + 1;
    }

    int gomgomRank;
    if (mode == 0) {
        gomgomRank = rnd.next(1, n);
    } else if (mode == 1) {
        gomgomRank = 1;
    } else if (mode == 2) {
        gomgomRank = n;
    } else if (mode == 3) {
        gomgomRank = rnd.next(max(1, n / 2 - 1), min(n, n / 2 + 1));
    } else {
        gomgomRank = rnd.next(1, n);
    }

    skills[0] = n - gomgomRank + 1;
    vector<int> rest;
    for (int value = 1; value <= n; ++value) {
        if (value != skills[0]) {
            rest.push_back(value);
        }
    }
    shuffle(rest.begin(), rest.end());
    for (int i = 1; i < n; ++i) {
        skills[i] = rest[i - 1];
    }

    int scale = rnd.next(0, 3);
    int multiplier = 1;
    if (scale == 1) {
        multiplier = rnd.next(10, 100);
    } else if (scale == 2) {
        multiplier = rnd.next(1000, 100000);
    }

    vector<int> prizes(k);
    for (int i = 0; i < k; ++i) {
        if (mode == 1) {
            prizes[i] = min(1000000, (i + 1) * multiplier);
        } else if (mode == 2) {
            prizes[i] = min(1000000, (k - i) * multiplier);
        } else if (mode == 3) {
            prizes[i] = (i % 2 == 0) ? rnd.next(1, 20) : rnd.next(999980, 1000000);
        } else {
            prizes[i] = rnd.next(1, 1000000);
        }
    }

    println(k);
    println(skills);
    println(prizes);
    return 0;
}
