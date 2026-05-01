#include "testlib.h"
using namespace std;

int randomOdd(int l, int h) {
    int x = rnd.next(l, h);
    if (x % 2 == 0) {
        if (x + 1 <= h) x++;
        else x--;
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> cand;
    int mode = rnd.next(0, 2);

    if (mode == 0) {
        // Many small consecutive odds
        int base[] = {7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41};
        cand.insert(cand.end(), base, base + (int)(sizeof(base)/sizeof(base[0])));
        int extraSmall = rnd.next(0, 5);
        for (int i = 0; i < extraSmall; ++i) {
            cand.push_back(randomOdd(43, 199));
        }
    } else if (mode == 1) {
        // Mixed small, medium, large, including sample-like values and edge-ish ones
        int base[] = {
            7,9,11,17,19,21,25,27,31,
            35,39,45,51,57,
            1929,1999,
            999991,999993,999995,999997,999999
        };
        cand.insert(cand.end(), base, base + (int)(sizeof(base)/sizeof(base[0])));

        int addSmall = rnd.next(0, 8);
        for (int i = 0; i < addSmall; ++i)
            cand.push_back(randomOdd(7, 199));

        int addMid = rnd.next(0, 8);
        for (int i = 0; i < addMid; ++i)
            cand.push_back(randomOdd(201, 10000));

        int addHigh = rnd.next(0, 8);
        for (int i = 0; i < addHigh; ++i)
            cand.push_back(randomOdd(10001, 999999));
    } else {
        // Mostly high values near the upper bound
        int base[] = {
            999983,999985,999987,999989,999991,
            999993,999995,999997,999999,
            500009,500011,500021
        };
        cand.insert(cand.end(), base, base + (int)(sizeof(base)/sizeof(base[0])));

        int addHigh = rnd.next(5, 20);
        for (int i = 0; i < addHigh; ++i)
            cand.push_back(randomOdd(500001, 999999));
    }

    // Deduplicate and shuffle
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());
    shuffle(cand.begin(), cand.end());

    int maxT = min((int)cand.size(), 40);
    int T = rnd.next(1, maxT);

    println(T);
    for (int i = 0; i < T; ++i)
        println(cand[i]);

    return 0;
}
