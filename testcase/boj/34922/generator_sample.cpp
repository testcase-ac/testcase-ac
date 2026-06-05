#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w;
    int h;
    int r;

    if (mode == 0) {
        w = rnd.next(1, 6);
        h = rnd.next(1, 6);
        r = rnd.next(1, min(w, h));
    } else if (mode == 1) {
        w = h = rnd.next(1, 100);
        r = rnd.next(1, w);
    } else if (mode == 2) {
        w = rnd.next(1, 100);
        h = rnd.next(1, 12);
        if (rnd.next(0, 1)) swap(w, h);
        r = rnd.next(1, min(w, h));
    } else if (mode == 3) {
        w = rnd.next(1, 100);
        h = rnd.next(1, 100);
        r = min(w, h);
    } else if (mode == 4) {
        w = rnd.next(1, 100);
        h = rnd.next(1, 100);
        r = 1;
    } else {
        w = rnd.next(1, 100);
        h = rnd.next(1, 100);
        r = rnd.next(1, min(w, h));
    }

    println(w, h);
    println(r);

    return 0;
}
