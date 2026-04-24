#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose shape of the grid
    int shape = rnd.next(0, 3);
    int R, C;
    if (shape == 0) {
        // square grid
        int s = rnd.next(2, 10);
        R = s;
        C = s;
    } else if (shape == 1) {
        // wide grid
        R = rnd.next(1, 3);
        C = rnd.next(4, 12);
    } else if (shape == 2) {
        // tall grid
        R = rnd.next(4, 12);
        C = rnd.next(1, 3);
    } else {
        // single row or single column
        if (rnd.next(0, 1) == 0) {
            R = 1;
            C = rnd.next(1, 12);
        } else {
            R = rnd.next(1, 12);
            C = 1;
        }
    }

    // Output a single test case
    println(R, C);
    return 0;
}
