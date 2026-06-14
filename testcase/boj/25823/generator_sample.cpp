#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m;

    if (mode == 0) {
        m = rnd.next(3, 12);
    } else if (mode == 1) {
        m = rnd.next(13, 200);
    } else if (mode == 2) {
        m = rnd.next(1000, 10000);
    } else if (mode == 3) {
        int center = rnd.any(std::vector<int>{100, 1000, 10000, 100000, 199999});
        m = center + rnd.next(-20, 20);
        if (m < 3) m = 3;
        if (m > 200000) m = 200000;
    } else if (mode == 4) {
        m = rnd.next(190000, 200000);
    } else {
        m = rnd.next(3, 200000);
    }

    println(m);
    return 0;
}
