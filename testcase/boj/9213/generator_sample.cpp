#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int value, int low, int high) {
    return max(low, min(value, high));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        2, 3, 4, 6, 8, 10, 16, 20, 28, 32, 64, 100, 496, 8128,
        99991, 100000, 499999, 524288, 999983, 999999
    };

    int tests = rnd.next(4, 12);
    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 6);
        int start;
        int stop;
        int badness;

        if (mode == 0) {
            start = rnd.any(anchors);
            stop = start;
            badness = rnd.next(0, 999);
        } else if (mode == 1) {
            start = rnd.next(2, 80);
            stop = rnd.next(start, min(150, start + rnd.next(0, 70)));
            badness = rnd.next(0, 5);
        } else if (mode == 2) {
            int center = rnd.any(anchors);
            int radius = rnd.next(0, 20);
            start = clampValue(center - radius, 2, 999999);
            stop = clampValue(center + rnd.next(0, 20), start, 999999);
            badness = rnd.any(vector<int>{0, 1, 2, 3, 10, 999});
        } else if (mode == 3) {
            start = rnd.next(900000, 999999);
            stop = rnd.next(start, min(999999, start + rnd.next(0, 5000)));
            badness = rnd.next(0, 999);
        } else if (mode == 4) {
            start = rnd.next(2, 999000);
            stop = rnd.next(start, min(999999, start + rnd.next(100, 2000)));
            badness = rnd.next(0, 999);
        } else {
            start = rnd.next(2, 999999);
            stop = rnd.next(start, min(999999, start + rnd.next(0, 30)));
            badness = rnd.next(0, 3);
        }

        println(start, stop, badness);
    }

    println(0, 0, 0);
    return 0;
}
