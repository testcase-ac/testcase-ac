#include "testlib.h"
#include <algorithm>

using namespace std;

const long long MAX_A = 1000000000000LL;
const long long MAX_WIDTH = 1000000LL;

long long clampStart(long long a, long long width) {
    a = max(1LL, a);
    a = min(a, MAX_A - width);
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a;
    long long width;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        a = rnd.next(1LL, 200LL);
        width = rnd.next(0LL, min(MAX_WIDTH, 500LL - a));
    } else if (mode == 1) {
        a = rnd.next(1LL, MAX_A);
        width = 0;
    } else if (mode == 2) {
        width = rnd.next(0LL, MAX_WIDTH);
        a = rnd.next(1LL, MAX_A - width);
    } else if (mode == 3) {
        width = rnd.next(MAX_WIDTH - 5000LL, MAX_WIDTH);
        a = rnd.next(1LL, MAX_A - width);
    } else if (mode == 4) {
        width = rnd.next(0LL, MAX_WIDTH);
        a = rnd.next(max(1LL, MAX_A - MAX_WIDTH * 3), MAX_A - width);
    } else if (mode == 5) {
        long long root = rnd.next(1LL, 1000000LL);
        long long center = root * root;
        width = rnd.next(0LL, 2000LL);
        long long offset = rnd.next(0LL, width);
        a = clampStart(center - offset, width);
    } else if (mode == 6) {
        long long base = rnd.next(1LL, 1000000LL);
        long long multiple = rnd.next(1LL, MAX_A / base);
        long long center = base * multiple;
        width = rnd.next(0LL, MAX_WIDTH);
        long long offset = rnd.next(0LL, width);
        a = clampStart(center - offset, width);
    } else {
        width = rnd.next(0LL, 10000LL);
        a = rnd.next(1LL, min(10000000LL, MAX_A - width));
    }

    println(a, a + width);
    return 0;
}
