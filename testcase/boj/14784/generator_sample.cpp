#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int value) {
    return max(1, min(1000000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int start = 1;
    int end = 1;

    if (mode == 0) {
        start = rnd.next(1, 80);
        end = rnd.next(start, min(120, start + rnd.next(0, 40)));
    } else if (mode == 1) {
        vector<int> anchors = {6, 28, 220, 284, 496, 1184, 1210, 2924, 5020,
                               5564, 6232, 6368, 8128, 10744, 10856};
        int anchor = rnd.any(anchors);
        int left = rnd.next(0, 80);
        int right = rnd.next(0, 160);
        start = clampValue(anchor - left);
        end = clampValue(anchor + right);
    } else if (mode == 2) {
        int width = rnd.next(0, 300);
        end = rnd.next(max(1, 1000000 - 1000), 1000000);
        start = max(1, end - width);
    } else if (mode == 3) {
        int width = rnd.next(0, 2000);
        start = rnd.next(1, 1000000 - width);
        end = start + width;
    } else if (mode == 4) {
        int center = rnd.next(1000, 200000);
        int width = rnd.next(1, 5000);
        start = clampValue(center - rnd.next(0, width));
        end = clampValue(center + rnd.next(0, width));
    } else {
        start = rnd.next(1, 1000000);
        end = rnd.next(start, min(1000000, start + rnd.next(0, 25)));
    }

    println(start, end);
    return 0;
}
