#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.any(std::vector<int>{2, 3, 10, 30});
    } else if (mode == 1) {
        n = rnd.next(2, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 10);
    } else {
        n = rnd.next(11, 30);
    }

    println(n);
    return 0;
}
