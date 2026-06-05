#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

using Die = array<int, 4>;

Die randomDie(int lo, int hi) {
    Die die{};
    for (int& face : die) {
        face = rnd.next(lo, hi);
    }
    return die;
}

Die shiftedDie(const Die& base, int delta) {
    Die die{};
    for (int i = 0; i < 4; ++i) {
        die[i] = clamp(base[i] + delta + rnd.next(-1, 1), 1, 10);
    }
    return die;
}

void shuffleDie(Die& die) {
    shuffle(die.begin(), die.end());
}

void printCase(Die a, Die b) {
    if (rnd.next(2) == 0) {
        sort(a.begin(), a.end());
    } else {
        shuffleDie(a);
    }

    if (rnd.next(2) == 0) {
        sort(b.begin(), b.end());
    } else {
        shuffleDie(b);
    }

    for (int i = 0; i < 4; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    for (int i = 0; i < 4; ++i) {
        cout << ' ' << b[i];
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    vector<pair<Die, Die>> anchors = {
        {{{4, 5, 6, 7}}, {{2, 4, 5, 10}}},
        {{{1, 1, 1, 1}}, {{2, 2, 2, 2}}},
        {{{1, 2, 3, 4}}, {{5, 6, 7, 8}}},
        {{{2, 4, 6, 8}}, {{1, 3, 5, 7}}},
        {{{9, 1, 9, 1}}, {{2, 10, 2, 10}}},
    };

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        Die a{};
        Die b{};

        if (mode == 0) {
            int x = rnd.next(1, 10);
            int y = rnd.next(1, 10);
            a = {x, x, x, x};
            b = {y, y, y, y};
        } else if (mode == 1) {
            int lo = rnd.next(1, 7);
            int hi = rnd.next(lo + 1, min(10, lo + 3));
            a = randomDie(lo, hi);
            b = randomDie(lo, hi);
        } else if (mode == 2) {
            int pivot = rnd.next(3, 8);
            a = {1, pivot, pivot, 10};
            b = {rnd.next(1, 3), rnd.next(4, 6), rnd.next(5, 8), rnd.next(8, 10)};
        } else if (mode == 3) {
            a = randomDie(1, 10);
            b = shiftedDie(a, rnd.next(-3, 3));
        } else if (mode == 4) {
            auto [baseA, baseB] = rnd.any(anchors);
            a = shiftedDie(baseA, rnd.next(-1, 1));
            b = shiftedDie(baseB, rnd.next(-1, 1));
        } else {
            a = randomDie(1, 10);
            b = randomDie(1, 10);
        }

        printCase(a, b);
    }

    return 0;
}
