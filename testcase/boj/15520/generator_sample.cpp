#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampLeft(long long l, int width) {
    l = max(1LL, l);
    l = min(l, 1000000000LL - width);
    return (int)l;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int width = 0;
    long long left = 1;

    if (mode == 0) {
        width = 0;
        vector<int> points = {1, 2, 4, 8, 12, 180, 999983, 1000000000};
        left = rnd.any(points);
    } else if (mode == 1) {
        width = rnd.next(1, 30);
        left = rnd.next(1, 500);
    } else if (mode == 2) {
        width = rnd.next(100, 5000);
        left = rnd.next(1, 1000000);
    } else if (mode == 3) {
        width = rnd.next(900000, 999999);
        left = rnd.next(1, 1000000000 - width);
    } else if (mode == 4) {
        width = rnd.next(1, 999999);
        left = 1000000000LL - width - rnd.next(0, 1000);
    } else if (mode == 5) {
        vector<int> anchors = {1024, 4096, 46656, 59049, 720720, 999983, 100000000};
        width = rnd.next(0, 2000);
        left = 1LL * rnd.any(anchors) - rnd.next(0, width);
    } else {
        width = rnd.next(0, 999999);
        left = rnd.next(1, 1000000000 - width);
    }

    int l = clampLeft(left, width);
    int r = l + width;
    println(l, r);

    return 0;
}
