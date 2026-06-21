#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 25);
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 25) + 1;
    } else if (mode == 3) {
        n = rnd.next(450, 500);
    } else if (mode == 4) {
        n = rnd.any(std::vector<int>{2, 3, 4, 5, 499, 500});
    } else {
        n = rnd.next(2, 500);
    }

    println(n);
    return 0;
}
