#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = rnd.next(0, 2);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.any(std::vector<int>{0, 1, n, n + 1});
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        k = rnd.next(0, n + 1);
    } else if (mode == 3) {
        n = rnd.next(50, 200);
        k = rnd.next(0, n + 1);
    } else if (mode == 4) {
        n = rnd.next(1000, 5000);
        k = rnd.any(std::vector<int>{0, 1, n / 2, n, n + 1});
    } else {
        n = 200000;
        k = rnd.any(std::vector<int>{0, 1, 199999, 200000, 200001});
    }

    println(n, k);
    return 0;
}
