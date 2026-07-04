#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr int MAX_N = 100000;

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 0) {
        t = 1;
    } else if (mode == 1) {
        t = rnd.next(2, 8);
    } else if (mode == 2) {
        t = rnd.next(8, 30);
    } else if (mode == 3) {
        t = rnd.next(30, 120);
    } else if (mode == 4) {
        t = rnd.next(1, 12);
    } else {
        t = rnd.next(1, 80);
    }

    vector<int> ns;
    ns.reserve(t);
    int remaining = MAX_N;

    for (int i = 0; i < t; ++i) {
        int casesLeft = t - i;
        int maxHere = remaining - (casesLeft - 1);
        int n;

        if (mode == 0) {
            n = rnd.next(1, MAX_N);
        } else if (mode == 1) {
            n = rnd.next(1, min(maxHere, 20));
        } else if (mode == 2) {
            n = rnd.next(1, min(maxHere, 500));
        } else if (mode == 3) {
            n = rnd.next(1, min(maxHere, 50));
        } else if (mode == 4 && i == 0) {
            n = rnd.next(max(1, maxHere - 1000), maxHere);
        } else {
            int smallCap = min(maxHere, 100);
            n = rnd.next() < 0.75 ? rnd.next(1, smallCap) : rnd.next(1, maxHere);
        }

        ns.push_back(n);
        remaining -= n;
    }

    if (mode == 5) {
        shuffle(ns.begin(), ns.end());
    }

    println(t);
    for (int n : ns) {
        printf("\n");
        println(n);
    }

    return 0;
}
