#include "testlib.h"

#include <vector>

using namespace std;

long long randomCard(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

void fillRandom(vector<long long>& cards, long long lo, long long hi) {
    for (long long& card : cards) {
        card = randomCard(lo, hi);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 24);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(25, 80);
    }

    vector<long long> cards(n);

    if (mode == 0) {
        fillRandom(cards, -20, 20);
    } else if (mode == 1) {
        fillRandom(cards, -30, -1);
    } else if (mode == 2) {
        fillRandom(cards, -15, 15);
        int prefixLen = rnd.next(1, n);
        long long high = randomCard(10, 100);
        for (int i = 0; i < prefixLen; ++i) {
            cards[i] = high + randomCard(-3, 3);
        }
        for (int i = prefixLen; i < n; ++i) {
            cards[i] = randomCard(-100, 5);
        }
    } else if (mode == 3) {
        fillRandom(cards, -15, 15);
        int suffixStart = rnd.next(0, n - 1);
        long long high = randomCard(10, 100);
        for (int i = 0; i < suffixStart; ++i) {
            cards[i] = randomCard(-100, 5);
        }
        for (int i = suffixStart; i < n; ++i) {
            cards[i] = high + randomCard(-3, 3);
        }
    } else if (mode == 4) {
        fillRandom(cards, -50, 50);
        int badL = rnd.next(0, n - 1);
        int badR = rnd.next(badL, n - 1);
        for (int i = badL; i <= badR; ++i) {
            cards[i] = randomCard(-200, -50);
        }
        if (badL > 0) {
            cards[rnd.next(0, badL - 1)] = randomCard(50, 200);
        }
        if (badR + 1 < n) {
            cards[rnd.next(badR + 1, n - 1)] = randomCard(50, 200);
        }
    } else {
        fillRandom(cards, -1000000000LL, 1000000000LL);
        int guaranteedPositive = rnd.next(0, n - 1);
        cards[guaranteedPositive] = randomCard(900000000LL, 1000000000LL);
        if (n > 1) {
            int guaranteedNegative = rnd.next(0, n - 1);
            while (guaranteedNegative == guaranteedPositive) {
                guaranteedNegative = rnd.next(0, n - 1);
            }
            cards[guaranteedNegative] = randomCard(-1000000000LL, -900000000LL);
        }
    }

    println(n);
    println(cards);

    return 0;
}
