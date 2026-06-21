#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(100);
    int n;

    if (mode < 20) {
        n = rnd.any(std::vector<int>{0, 1, 2, 999, 1000});
    } else if (mode < 55) {
        n = rnd.next(0, 10);
    } else if (mode < 80) {
        n = rnd.next(11, 100);
    } else {
        n = rnd.next(101, 1000);
    }

    println(n);
    return 0;
}
