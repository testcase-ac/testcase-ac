#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int l;
    int k;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        l = rnd.next(1, 8);
        k = rnd.next(2, 10);
    } else if (mode == 1) {
        l = rnd.next(90, 100);
        k = rnd.next(2, 10);
    } else if (mode == 2) {
        l = rnd.next(1, 9);
        k = rnd.next(l + 1, 10);
    } else if (mode == 3) {
        k = rnd.next(2, 10);
        l = rnd.next(k, 100);
    } else if (mode == 4) {
        l = rnd.next(1, 100);
        k = rnd.any(std::vector<int>{2, 3, 5, 10});
    } else {
        l = rnd.next(1, 100);
        k = rnd.next(2, 10);
    }

    println(l, k);
    return 0;
}
