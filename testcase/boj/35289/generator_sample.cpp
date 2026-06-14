#include "testlib.h"

#include <array>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_COUNT = 1000000;
    array<int, 6> cnt{};
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        cnt[rnd.next(0, 5)] = rnd.next(1, 5);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 20);
        cnt[0] = rnd.next(0, pairs);
        cnt[2] = cnt[0];
        int remaining = pairs - cnt[0];
        cnt[1] = rnd.next(0, remaining);
        cnt[3] = remaining - cnt[1];
        cnt[4] = rnd.next(0, 20);
        cnt[5] = rnd.next(0, 20);
    } else if (mode == 2) {
        cnt[0] = rnd.next(0, 30);
        cnt[1] = rnd.next(0, 30);
        cnt[2] = rnd.next(0, 2);
        cnt[3] = rnd.next(0, 2);
        cnt[4] = rnd.next(0, 5);
        cnt[5] = rnd.next(0, 5);
    } else if (mode == 3) {
        cnt[0] = rnd.next(0, 2);
        cnt[1] = rnd.next(0, 2);
        cnt[2] = rnd.next(0, 30);
        cnt[3] = rnd.next(0, 30);
        cnt[4] = rnd.next(0, 5);
        cnt[5] = rnd.next(0, 5);
    } else if (mode == 4) {
        cnt[0] = rnd.next(0, 10);
        cnt[1] = rnd.next(0, 10);
        cnt[2] = rnd.next(0, 10);
        cnt[3] = rnd.next(0, 10);
        cnt[4] = rnd.next(20, 80);
        cnt[5] = rnd.next(0, 80);
    } else if (mode == 5) {
        cnt[0] = rnd.next(0, 10);
        cnt[1] = rnd.next(0, 10);
        cnt[2] = rnd.next(0, 10);
        cnt[3] = rnd.next(0, 10);
        cnt[4] = rnd.next(0, 10);
        cnt[5] = rnd.next(20, 80);
    } else if (mode == 6) {
        int hi = rnd.next(30, 200);
        for (int i = 0; i < 6; ++i) {
            cnt[i] = rnd.next(0, hi);
        }
    } else {
        int high = rnd.next(800000, MAX_COUNT);
        for (int i = 0; i < 6; ++i) {
            cnt[i] = rnd.next(0, high);
        }
        cnt[rnd.next(0, 5)] = high;
    }

    if (all_of(cnt.begin(), cnt.end(), [](int x) { return x == 0; })) {
        cnt[rnd.next(0, 5)] = 1;
    }

    println(cnt[0], cnt[1], cnt[2], cnt[3], cnt[4], cnt[5]);
    return 0;
}
