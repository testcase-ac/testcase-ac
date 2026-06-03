#include "testlib.h"
#include <array>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 2) {
        n = rnd.next(8, 25);
    } else if (mode == 3) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(20, 60);
    }

    vector<array<int, 5>> hands(n);

    if (mode == 0) {
        int repeated = rnd.next(1, 10);
        for (auto& hand : hands) {
            hand.fill(repeated);
        }
    } else if (mode == 1) {
        for (auto& hand : hands) {
            int lo = rnd.next(1, 8);
            int hi = rnd.next(lo, 10);
            for (int& card : hand) {
                card = rnd.next(lo, hi);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(1, 10);
            for (int j = 0; j < 5; ++j) {
                int delta = rnd.next(-2, 2);
                int value = base + delta;
                if (value < 1) value += 10;
                if (value > 10) value -= 10;
                hands[i][j] = value;
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int target = (i == n - 1 ? 9 : rnd.next(0, 8));
            int a = rnd.next(1, 10);
            int b = rnd.next(1, 10);
            int c = target - (a + b);
            c %= 10;
            if (c <= 0) c += 10;
            hands[i] = {a, b, c, rnd.next(1, 10), rnd.next(1, 10)};
            shuffle(hands[i].begin(), hands[i].end());
        }
    } else {
        for (auto& hand : hands) {
            for (int& card : hand) {
                card = rnd.next(1, 10);
            }
        }
    }

    println(n);
    for (const auto& hand : hands) {
        println(hand[0], hand[1], hand[2], hand[3], hand[4]);
    }

    return 0;
}
