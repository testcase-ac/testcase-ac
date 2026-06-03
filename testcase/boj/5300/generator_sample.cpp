#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        int boats = rnd.next(1, 20);
        n = boats * 6;
    } else if (mode == 2) {
        int boats = rnd.next(1, 20);
        int offset = rnd.any(std::vector<int>{-1, 1});
        n = boats * 6 + offset;
    } else if (mode == 3) {
        n = rnd.next(13, 200);
    } else {
        n = maxN - rnd.next(0, 30);
    }

    println(n);
    return 0;
}
