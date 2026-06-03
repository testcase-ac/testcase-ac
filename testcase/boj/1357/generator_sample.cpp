#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x = 1;
    int y = 1;

    if (mode == 0) {
        x = rnd.next(1, 9);
        y = rnd.next(1, 9);
    } else if (mode == 1) {
        vector<int> bases = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        vector<int> scale = {10, 100, 1000};
        x = rnd.any(bases) * rnd.any(scale);
        y = rnd.next(1, 1000);
        if (x > 1000) x = 1000;
    } else if (mode == 2) {
        vector<int> carries = {59, 68, 77, 86, 95, 149, 248, 347, 446, 545, 644, 743, 842, 941};
        x = rnd.any(carries);
        y = rnd.any(carries);
    } else if (mode == 3) {
        x = rnd.next(900, 1000);
        y = rnd.next(900, 1000);
    } else if (mode == 4) {
        x = rnd.next(1, 1000);
        y = rnd.next(1, 1000);
        if (rnd.next(0, 1)) x = rnd.next(1, 9) * 100 + rnd.next(0, 9) * 10;
        if (rnd.next(0, 1)) y = rnd.next(1, 9) * 100 + rnd.next(0, 9) * 10;
    } else {
        x = rnd.next(1, 1000);
        y = rnd.next(1, 1000);
    }

    println(x, y);
    return 0;
}
