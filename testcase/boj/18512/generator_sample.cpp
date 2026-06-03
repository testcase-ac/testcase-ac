#include "testlib.h"

#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int x = 1;
    int y = 1;
    int p1 = 1;
    int p2 = 1;
    int mode = rnd.next(6);

    if (mode == 0) {
        x = y = rnd.next(1, 100);
        p1 = rnd.next(1, 100);
        p2 = rnd.next(1, 100);
    } else if (mode == 1) {
        int meet = rnd.next(20, 100);
        x = rnd.next(1, min(100, meet));
        y = rnd.next(1, min(100, meet));
        p1 = meet - rnd.next(0, (meet - 1) / x) * x;
        p2 = meet - rnd.next(0, (meet - 1) / y) * y;
    } else if (mode == 2) {
        int g = rnd.next(2, 20);
        x = g * rnd.next(1, 100 / g);
        y = g * rnd.next(1, 100 / g);
        p1 = rnd.next(1, 100);
        int residue = p1 % g;
        int otherResidue = rnd.next(0, g - 2);
        if (otherResidue >= residue) ++otherResidue;
        p2 = otherResidue + 1;
        while (p2 + g <= 100 && rnd.next(2)) p2 += g;
    } else if (mode == 3) {
        x = rnd.next(80, 100);
        y = rnd.next(80, 100);
        p1 = rnd.next(1, 100);
        p2 = rnd.next(1, 100);
    } else if (mode == 4) {
        x = rnd.next(1, 8);
        y = rnd.next(1, 8);
        p1 = rnd.next(1, 20);
        p2 = rnd.next(1, 20);
    } else {
        x = rnd.next(1, 100);
        y = rnd.next(1, 100);
        int g = gcd(x, y);
        p1 = rnd.next(1, 100);
        int offset = rnd.next(0, (100 - p1) / g);
        p2 = p1 + offset * g;
    }

    println(x, y, p1, p2);
    return 0;
}
