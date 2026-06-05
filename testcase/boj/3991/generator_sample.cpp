#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h, w, c;

    if (mode == 0) {
        h = w = c = 1;
    } else if (mode == 1) {
        h = rnd.next(1, 10);
        w = rnd.next(1, 10);
        c = 1;
    } else if (mode == 2) {
        h = rnd.any(vector<int>{1, 2, 10});
        w = rnd.next(1, 10);
        if (rnd.next(2) == 0) swap(h, w);
        c = rnd.next(1, min(9, h * w));
    } else if (mode == 3) {
        h = rnd.next(2, 5);
        w = rnd.next(2, 5);
        c = min(9, h * w);
    } else if (mode == 4) {
        h = rnd.next(6, 10);
        w = rnd.next(6, 10);
        c = rnd.next(2, min(9, h * w));
    } else {
        h = rnd.next(1, 10);
        w = rnd.next(1, 10);
        c = rnd.next(1, min(9, h * w));
    }

    int cells = h * w;
    vector<int> counts(c, 1);
    int extra = cells - c;

    int distribution = rnd.next(0, 3);
    if (distribution == 0) {
        counts[rnd.next(c)] += extra;
    } else if (distribution == 1) {
        for (int i = 0; i < extra; ++i) {
            counts[i % c]++;
        }
        shuffle(counts.begin(), counts.end());
    } else if (distribution == 2) {
        while (extra > 0) {
            int add = rnd.next(1, extra);
            counts[rnd.next(c)] += add;
            extra -= add;
        }
    } else {
        for (int i = 0; i < extra; ++i) {
            counts[rnd.wnext(c, 2)]++;
        }
    }

    println(h, w, c);
    println(counts);

    return 0;
}
