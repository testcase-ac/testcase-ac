#include "testlib.h"

#include <vector>
using namespace std;

const int FIRST = 1;
const int LAST = 11172;
const int FINAL_COUNT = 28;
const int MEDIAL_BLOCK = 28;
const int INITIAL_BLOCK = 21 * 28;

int clampN(int value) {
    if (value < FIRST) return FIRST;
    if (value > LAST) return LAST;
    return value;
}

int nearBoundary(int period) {
    int block = rnd.next(0, (LAST - 1) / period);
    int base = block * period + 1;
    int offset = rnd.any(vector<int>{0, 1, period - 2, period - 1});
    return clampN(base + offset);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.any(vector<int>{FIRST, FIRST + 1, LAST - 1, LAST});
    } else if (mode == 1) {
        n = nearBoundary(FINAL_COUNT);
    } else if (mode == 2) {
        n = nearBoundary(INITIAL_BLOCK);
    } else if (mode == 3) {
        int center = rnd.any(vector<int>{MEDIAL_BLOCK, INITIAL_BLOCK, LAST / 2, LAST});
        n = clampN(center + rnd.next(-30, 30));
    } else {
        n = rnd.next(FIRST, LAST);
    }

    println(n);
    return 0;
}
