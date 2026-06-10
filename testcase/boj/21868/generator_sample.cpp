#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int en;
    int ed;
    int c;
    int d;
    int x0;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        en = rnd.next(1, 20);
        ed = rnd.next(1, 20);
        c = 0;
        d = rnd.next(-20, 20);
        x0 = rnd.next(-20, 20);
    } else if (mode == 1) {
        en = rnd.next(1, 12);
        ed = rnd.next(1, 12);
        c = rnd.any(std::vector<int>{-3, -2, -1, 1, 2, 3});
        d = rnd.next(-12, 12);
        x0 = rnd.next(-12, 12);
    } else if (mode == 2) {
        en = rnd.next(9990, 10000);
        ed = rnd.next(1, 10);
        c = rnd.any(std::vector<int>{-10000, -9999, 9999, 10000});
        d = rnd.next(-10000, 10000);
        x0 = rnd.next(-10000, 10000);
    } else if (mode == 3) {
        en = rnd.next(1, 10);
        ed = rnd.next(9990, 10000);
        c = rnd.next(-10000, 10000);
        if (c == 0) c = rnd.any(std::vector<int>{-1, 1});
        d = rnd.any(std::vector<int>{-10000, 10000});
        x0 = rnd.any(std::vector<int>{-10000, 10000});
    } else if (mode == 4) {
        en = rnd.next(1, 10000);
        ed = rnd.next(1, 10000);
        c = rnd.next(-20, 20);
        if (c == 0) c = rnd.any(std::vector<int>{-20, 20});
        d = -c * rnd.next(-10, 10);
        x0 = rnd.next(-10, 10);
    } else {
        en = rnd.next(1, 10000);
        ed = rnd.next(1, 10000);
        c = rnd.next(-10000, 10000);
        d = rnd.next(-10000, 10000);
        x0 = rnd.next(-10000, 10000);
    }

    println(en, ed);
    println(c, d);
    println(x0);

    return 0;
}
