#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n;
    if (mode == 0) {
        n = rnd.any(std::vector<int>{1, 10});
    } else if (mode == 1) {
        n = rnd.next(1, 4);
    } else if (mode == 2) {
        n = rnd.next(5, 10);
    } else {
        n = rnd.next(1, 10);
    }

    println(n);
    return 0;
}
