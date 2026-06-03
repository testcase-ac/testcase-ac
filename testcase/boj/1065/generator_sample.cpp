#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        vector<int> edges = {1, 2, 9, 10, 11, 98, 99, 100, 101, 109, 110, 111, 210, 500, 999, 1000};
        n = rnd.any(edges);
    } else if (mode == 1) {
        n = rnd.next(1, 99);
    } else if (mode == 2) {
        n = rnd.next(100, 150);
    } else if (mode == 3) {
        int hundreds = rnd.next(1, 9);
        int tens = rnd.next(0, 9);
        int delta = tens - hundreds;
        int ones = tens + delta;
        if (0 <= ones && ones <= 9) {
            n = 100 * hundreds + 10 * tens + ones;
        } else {
            n = 100 * hundreds + 10 * tens + rnd.next(0, 9);
        }
    } else if (mode == 4) {
        n = rnd.next(900, 1000);
    } else {
        n = rnd.next(1, 1000);
    }

    println(n);
    return 0;
}
