#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.any(std::vector<int>{1, 2, 3, 17, 998, 999});
    } else if (mode == 1) {
        n = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 80);
    } else if (mode == 3) {
        n = rnd.next(81, 250);
    } else if (mode == 4) {
        n = rnd.next(251, 999);
    } else {
        int base = rnd.next(1, 125) * 8;
        n = base + rnd.next(-3, 3);
        if (n < 1) n = 1;
        if (n > 999) n = 999;
    }

    println(n);
    return 0;
}
