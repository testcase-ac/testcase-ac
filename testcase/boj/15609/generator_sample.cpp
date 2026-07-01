#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> ratings;

    if (mode == 0) {
        vector<int> powers = {2, 4, 8, 16};
        n = rnd.any(powers);
    } else if (mode == 1) {
        vector<int> nearPowers = {3, 5, 6, 7, 9, 15, 17};
        n = rnd.any(nearPowers);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
    } else if (mode == 3) {
        n = rnd.next(18, 40);
    } else {
        n = rnd.next(2, 24);
    }

    ratings.resize(n);

    if (mode == 2) {
        int common = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            ratings[i] = rnd.next(0, 4) == 0 ? rnd.next(1, 30) : common;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            ratings[i] = rnd.next(1, 100000);
        }
    } else {
        int lo = rnd.next(1, 30);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 500)));
        for (int i = 0; i < n; ++i) {
            ratings[i] = rnd.next(lo, hi);
        }
    }

    int dalePattern = rnd.next(0, 3);
    if (dalePattern == 0) {
        ratings[0] = 1;
    } else if (dalePattern == 1) {
        ratings[0] = 100000;
    } else if (dalePattern == 2) {
        ratings[0] = rnd.next(1, 10);
    }

    if (n > 2 && rnd.next(0, 1)) {
        shuffle(ratings.begin() + 1, ratings.end());
    }

    println(n);
    for (int rating : ratings) {
        println(rating);
    }

    return 0;
}
