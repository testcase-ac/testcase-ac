#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedRating(long long value) {
    return (int)min(1000000LL, max(1LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 5) {
        n = 2 * rnd.next(20, 80);
    } else {
        n = 2 * rnd.next(2, 12);
    }

    vector<int> ratings;
    ratings.reserve(n);

    if (mode == 0) {
        ratings.push_back(rnd.next(1, 1000000));
        ratings.push_back(rnd.next(1, 1000000));
    } else if (mode == 1) {
        int value = rnd.next(1, 1000000);
        ratings.assign(n, value);
    } else if (mode == 2) {
        int lo = rnd.next(1, 50);
        int hi = rnd.next(999950, 1000000);
        for (int i = 0; i < n / 2; ++i) ratings.push_back(rnd.next(lo, min(1000000, lo + 100)));
        for (int i = n / 2; i < n; ++i) ratings.push_back(rnd.next(max(1, hi - 100), hi));
    } else if (mode == 3) {
        int target = rnd.next(2, 2000000);
        for (int i = 0; i < n / 2; ++i) {
            int a = rnd.next(1, 1000000);
            int b = boundedRating(target - a + rnd.next(-3, 3));
            ratings.push_back(a);
            ratings.push_back(b);
        }
    } else if (mode == 4) {
        int base = rnd.next(1, 999900);
        for (int i = 0; i < n; ++i) ratings.push_back(boundedRating(base + rnd.next(0, 100)));
    } else {
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(4);
            if (bucket == 0) ratings.push_back(rnd.next(1, 20));
            else if (bucket == 1) ratings.push_back(rnd.next(21, 1000));
            else if (bucket == 2) ratings.push_back(rnd.next(1001, 100000));
            else ratings.push_back(rnd.next(900000, 1000000));
        }
    }

    shuffle(ratings.begin(), ratings.end());

    println(n);
    for (int rating : ratings) println(rating);

    return 0;
}
