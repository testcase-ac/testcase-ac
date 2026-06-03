#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r;
    int c;

    if (mode == 0) {
        r = rnd.next(1, 6);
        c = 1;
    } else if (mode == 1) {
        r = rnd.next(1, 29);
        c = r;
    } else if (mode == 2) {
        r = rnd.next(3, 18);
        c = rnd.next(2, r - 1);
    } else if (mode == 3) {
        r = rnd.next(20, 29);
        c = rnd.next(max(1, r - 5), r);
    } else if (mode == 4) {
        r = rnd.next(1, 29);
        c = rnd.next(1, r);
    } else {
        r = rnd.wnext(29, 3) + 1;
        c = rnd.next(1, r);
    }

    int maxW = min(30 - r, 30 - c);
    int w;
    if (mode == 0) {
        w = rnd.next(max(1, maxW - 8), maxW);
    } else if (mode == 3) {
        w = rnd.next(1, min(maxW, 5));
    } else if (mode == 5) {
        w = rnd.wnext(maxW, 2) + 1;
    } else {
        w = rnd.next(1, maxW);
    }

    println(r, c, w);
    return 0;
}
