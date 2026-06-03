#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_R = 2;
    const long long MAX_R = 1000000000LL;

    vector<long long> anchors = {
        MIN_R,
        3,
        10,
        100,
        1000,
        100000,
        1000000,
        31622776,
        100000000,
        MAX_R,
    };

    int mode = rnd.next(0, 5);
    long long r;
    if (mode == 0) {
        r = rnd.next(MIN_R, 50LL);
    } else if (mode == 1) {
        r = rnd.next(MIN_R, 1000LL);
    } else if (mode == 2) {
        r = rnd.next(1000LL, 100000LL);
    } else if (mode == 3) {
        r = rnd.next(100000LL, MAX_R);
    } else {
        long long anchor = rnd.any(anchors);
        long long delta = rnd.next(-25LL, 25LL);
        r = min(MAX_R, max(MIN_R, anchor + delta));
    }

    println(r);
    return 0;
}
