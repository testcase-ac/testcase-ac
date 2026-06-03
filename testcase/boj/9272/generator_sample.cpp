#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr int kMinN = 1;
    constexpr int kMaxN = 10000;

    int n1;
    int n2;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n1 = rnd.next(kMinN, 20);
        n2 = rnd.next(n1 + 1, std::min(kMaxN, n1 + 50));
    } else if (mode == 1) {
        n2 = rnd.next(kMaxN - 50, kMaxN);
        n1 = rnd.next(std::max(kMinN, n2 - 50), n2 - 1);
    } else if (mode == 2) {
        n1 = rnd.next(kMinN, kMaxN - 1);
        n2 = n1 + 1;
    } else if (mode == 3) {
        int len = rnd.next(2, 100);
        n1 = rnd.next(kMinN, kMaxN - len + 1);
        n2 = n1 + len - 1;
    } else if (mode == 4) {
        int len = rnd.next(500, 3000);
        n1 = rnd.next(kMinN, kMaxN - len + 1);
        n2 = n1 + len - 1;
    } else {
        n1 = rnd.next(kMinN, kMaxN - 1);
        n2 = rnd.next(n1 + 1, kMaxN);
    }

    println(n1, n2);
    return 0;
}
