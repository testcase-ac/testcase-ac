#include "testlib.h"
#include <vector>
using namespace std;

long long pileFromValue(long long value) {
    if (value % 4 == 0) return value - 1;
    if (value % 4 == 3) return value + 1;
    return value;
}

long long randomPile(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<long long> piles;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) piles.push_back(randomPile(1, 20));
    } else if (mode == 1) {
        int n = rnd.next(2, 20);
        long long base = rnd.next(1, 200);
        base -= base % 4;
        if (base < 4) base = 4;
        for (int i = 0; i < n; ++i) {
            long long value = base + rnd.next(-3, 4);
            if (value < 1) value = 1;
            piles.push_back(value);
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 16);
        long long xsum = 0;
        for (int i = 0; i + 1 < n; ++i) {
            long long value = rnd.next(1, 1024);
            xsum ^= value;
            piles.push_back(pileFromValue(value));
        }
        if (xsum == 0) {
            long long replacement = rnd.next(1, 1024);
            piles.back() = pileFromValue(replacement);
            xsum = replacement;
            for (int i = 0; i + 2 < n; ++i) {
                long long value = piles[i];
                if (value % 4 == 0) xsum ^= value - 1;
                else if (value % 4 == 3) xsum ^= value + 1;
                else xsum ^= value;
            }
        }
        piles.push_back(pileFromValue(xsum));
    } else if (mode == 3) {
        int pairs = rnd.next(1, 25);
        for (int i = 0; i < pairs; ++i) {
            long long value = rnd.next(1, 5000);
            long long pile = pileFromValue(value);
            piles.push_back(pile);
            piles.push_back(pile);
        }
        if (rnd.next(0, 1)) piles.push_back(randomPile(1, 30));
    } else if (mode == 4) {
        int n = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            long long nearMax = 2000000000LL - rnd.next(0, 12);
            piles.push_back(nearMax);
        }
    } else {
        int n = rnd.next(20, 100);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) piles.push_back(randomPile(1, 50));
            else if (bucket == 1) piles.push_back(randomPile(1000, 100000));
            else piles.push_back(randomPile(1999999900LL, 2000000000LL));
        }
    }

    shuffle(piles.begin(), piles.end());
    println((int)piles.size());
    println(piles);

    return 0;
}
