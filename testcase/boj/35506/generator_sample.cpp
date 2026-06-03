#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.any(std::vector<int>{2, 3, 5, 10, 20});
    } else if (mode == 2) {
        n = rnd.next(7, 30);
    } else if (mode == 3) {
        n = rnd.next(31, 70);
    } else if (mode == 4) {
        n = rnd.next(71, 99);
    } else {
        n = 100;
    }

    println(n);
    return 0;
}
