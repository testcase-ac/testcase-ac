#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIM = 1000000;
    int a, b, c, d;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        a = rnd.next(1, 20);
        b = a;
        c = rnd.next(1, 20);
        d = c;
    } else if (mode == 1) {
        a = 1;
        b = rnd.next(1, 30);
        c = rnd.next(1, 30);
        d = rnd.next(c, min(LIM, c + rnd.next(0, 40)));
    } else if (mode == 2) {
        c = 1;
        d = rnd.next(1, 30);
        a = rnd.next(1, 30);
        b = rnd.next(a, min(LIM, a + rnd.next(0, 40)));
    } else if (mode == 3) {
        a = rnd.next(1, 100);
        b = rnd.next(a, min(LIM, a + rnd.next(0, 100)));
        c = rnd.next(1, 100);
        d = rnd.next(c, min(LIM, c + rnd.next(0, 100)));
    } else if (mode == 4) {
        a = rnd.next(1, 1000);
        b = rnd.next(a, LIM);
        c = rnd.next(1, 1000);
        d = rnd.next(c, LIM);
    } else if (mode == 5) {
        a = rnd.next(900000, LIM);
        b = rnd.next(a, LIM);
        c = rnd.next(900000, LIM);
        d = rnd.next(c, LIM);
    } else if (mode == 6) {
        int width1 = rnd.next(0, 10);
        int width2 = rnd.next(0, 10);
        a = rnd.next(1, LIM - width1);
        b = a + width1;
        c = rnd.next(1, LIM - width2);
        d = c + width2;
    } else {
        a = rnd.next(1, LIM);
        b = rnd.next(a, LIM);
        c = rnd.next(1, LIM);
        d = rnd.next(c, LIM);
    }

    println(a, b, c, d);
    return 0;
}
