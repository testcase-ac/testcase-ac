#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // BOJ 1022 constraints:
    // -5000 <= r1, c1, r2, c2 <= 5000
    // 0 <= r2 - r1 <= 49
    // 0 <= c2 - c1 <= 49
    const int minCoord = -5000;
    const int maxCoord = 5000;

    int height = rnd.next(0, 49);  // r2 - r1
    int width = rnd.next(0, 49);   // c2 - c1

    int r1 = rnd.next(minCoord, maxCoord - height);
    int c1 = rnd.next(minCoord, maxCoord - width);
    int r2 = r1 + height;
    int c2 = c1 + width;

    println(r1, c1, r2, c2);
    return 0;
}
