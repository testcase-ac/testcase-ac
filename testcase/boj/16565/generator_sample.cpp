#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 52);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(40, 52);
    } else {
        int base = 4 * rnd.next(1, 13);
        int delta = rnd.next(-2, 2);
        n = max(1, min(52, base + delta));
    }

    println(n);
    return 0;
}
