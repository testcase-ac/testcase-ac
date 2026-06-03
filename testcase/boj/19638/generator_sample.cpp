#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 25);
    long long hCenti = rnd.next(1LL, 2000000000LL);
    int t = rnd.next(1, 60);
    vector<long long> heights;

    if (mode == 0) {
        hCenti = rnd.next(2LL, 80LL);
        t = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            long long lo = max(1LL, hCenti - 5);
            long long hi = min(2000000000LL, hCenti + 25);
            heights.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 1) {
        hCenti = rnd.next(1LL, 20LL);
        t = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            heights.push_back(rnd.next(0, 2) == 0 ? 1LL : rnd.next(1LL, 40LL));
        }
    } else if (mode == 2) {
        hCenti = rnd.next(2LL, 1000LL);
        t = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int shifts = rnd.next(0, 10);
            long long base = min(2000000000LL, hCenti << min(shifts, 20));
            long long wiggle = rnd.next(-3LL, 3LL);
            heights.push_back(max(1LL, min(2000000000LL, base + wiggle)));
        }
    } else if (mode == 3) {
        hCenti = rnd.next(1500000000LL, 2000000000LL);
        t = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            heights.push_back(rnd.next(1800000000LL, 2000000000LL));
        }
    } else if (mode == 4) {
        hCenti = rnd.next(2LL, 200LL);
        t = rnd.next(1, 12);
        long long tall = rnd.next(hCenti, min(2000000000LL, hCenti * rnd.next(2LL, 1000000LL)));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                heights.push_back(tall);
            } else {
                heights.push_back(rnd.next(1LL, max(1LL, hCenti + 20)));
            }
        }
    } else {
        n = rnd.next(1, 100);
        hCenti = rnd.next(1LL, 2000000000LL);
        t = rnd.next(1, 100000);
        for (int i = 0; i < n; ++i) {
            heights.push_back(rnd.next(1LL, 2000000000LL));
        }
    }

    shuffle(heights.begin(), heights.end());

    println(n, hCenti, t);
    for (long long h : heights) {
        println(h);
    }

    return 0;
}
