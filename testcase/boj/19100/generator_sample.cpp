#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 7);
    } else {
        n = rnd.next(1, 6);
    }

    int card_count = 1 << n;
    int t;
    if (mode == 0) {
        t = rnd.any(vector<int>{1, 2, 999999999, 1000000000});
    } else if (mode == 1) {
        t = 2 * rnd.next(0, 20) + 1;
    } else if (mode == 2) {
        t = 2 * rnd.next(1, 20);
    } else {
        t = rnd.next(1, 1000000000);
    }

    vector<int> cards(card_count);
    if (mode == 3) {
        int value = rnd.any(vector<int>{1, 2, 999999999, 1000000000});
        for (int i = 0; i < card_count; ++i) {
            cards[i] = value;
        }
    } else if (mode == 4) {
        for (int i = 0; i < card_count; ++i) {
            cards[i] = (i % 2 == 0) ? 1 : 1000000000;
        }
        if (rnd.next(0, 1)) {
            shuffle(cards.begin(), cards.end());
        }
    } else if (mode == 5) {
        int start = rnd.next(1, 1000);
        int step = rnd.next(1, 1000);
        for (int i = 0; i < card_count; ++i) {
            cards[i] = start + i * step;
        }
        if (rnd.next(0, 1)) {
            shuffle(cards.begin(), cards.end());
        }
    } else {
        int hi = rnd.any(vector<int>{5, 20, 1000, 1000000000});
        for (int i = 0; i < card_count; ++i) {
            cards[i] = rnd.next(1, hi);
        }
    }

    println(n, t);
    println(cards);

    return 0;
}
