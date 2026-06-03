#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> special = {2025, 3025, 9801};
    int mode = rnd.next(0, 5);
    int x;

    if (mode == 0) {
        x = rnd.next(1000, 9999);
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            x = rnd.next(1000, 1010);
        } else {
            x = rnd.next(9989, 9999);
        }
    } else if (mode == 2) {
        int y = rnd.any(special);
        int delta = rnd.next(-4, 4);
        x = y + delta;
    } else if (mode == 3) {
        int y = rnd.any(special);
        x = rnd.next(max(1000, y - 120), y - 1);
    } else if (mode == 4) {
        int segment = rnd.next(0, 2);
        if (segment == 0) {
            x = rnd.next(2025, 3024);
        } else if (segment == 1) {
            x = rnd.next(3025, 9800);
        } else {
            x = rnd.next(9801, 9999);
        }
    } else {
        int century = rnd.next(10, 99);
        int year = rnd.next(0, 99);
        x = century * 100 + year;
    }

    x = max(1000, min(9999, x));
    println(x);
    return 0;
}
