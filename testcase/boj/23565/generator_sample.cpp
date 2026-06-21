#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_COUNT = 100000000000000000LL;

ll smallCount() {
    int mode = rnd.next(0, 5);
    if (mode <= 2) return rnd.next(0, 8);
    if (mode == 3) return rnd.next(9, 50);
    if (mode == 4) return rnd.next(51, 1000);
    return rnd.next(1001, 1000000);
}

ll largeCount() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return MAX_COUNT;
    if (mode == 1) return MAX_COUNT - rnd.next(0, 1000);
    if (mode == 2) return rnd.next(1000000000000LL, MAX_COUNT);
    if (mode == 3) return rnd.next(1000000LL, 1000000000000LL);
    return smallCount();
}

array<ll, 4> randomCase() {
    int mode = rnd.next(0, 9);
    array<ll, 4> v = {0, 0, 0, 0};

    if (mode == 0) {
        v = {smallCount(), 0, 0, 0};
    } else if (mode == 1) {
        v = {0, 0, smallCount(), 0};
    } else if (mode == 2) {
        v = {rnd.next(0, 2), 0, 0, smallCount()};
    } else if (mode == 3) {
        v = {rnd.next(0, 1), 0, rnd.next(1, 6), smallCount()};
    } else if (mode == 4) {
        v = {0, rnd.next(1, 8), smallCount(), rnd.next(0, 8)};
    } else if (mode == 5) {
        v = {rnd.next(0, 2), rnd.next(0, 1), rnd.next(0, 3), rnd.next(0, 3)};
    } else if (mode == 6) {
        v = {rnd.next(3, 20), smallCount(), smallCount(), smallCount()};
    } else if (mode == 7) {
        v = {largeCount(), rnd.next(0, 1) ? largeCount() : 0,
             rnd.next(0, 1) ? largeCount() : 0, rnd.next(0, 1) ? largeCount() : 0};
    } else if (mode == 8) {
        v = {rnd.next(0, 2), 0, largeCount(), largeCount()};
    } else {
        v = {largeCount(), largeCount(), largeCount(), largeCount()};
    }

    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<array<ll, 4>> cases = {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {2, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 2, 0},
        {0, 0, 3, 1},
        {1, 0, 1, 1},
        {2, 0, 1, 1},
        {1, 1, 0, 1},
        {MAX_COUNT, 0, 0, 0},
        {0, MAX_COUNT, 0, MAX_COUNT},
        {MAX_COUNT, MAX_COUNT, MAX_COUNT, MAX_COUNT},
    };

    int extra = rnd.next(6, 26);
    while (extra--) {
        cases.push_back(randomCase());
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const auto& v : cases) {
        println(v[0], v[1], v[2], v[3]);
    }

    return 0;
}
