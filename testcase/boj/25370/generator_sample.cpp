#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    int n;
    if (mode == 0) {
        n = rnd.any(std::vector<int>{1, 7});
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(1, 7);
    }

    println(n);
    return 0;
}
