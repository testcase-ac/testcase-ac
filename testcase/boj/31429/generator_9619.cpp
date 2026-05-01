#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // Best rank
        N = 1;
    } else if (mode == 1) {
        // Worst rank
        N = 11;
    } else if (mode == 2) {
        // Middle rank fixed
        N = 6;
    } else if (mode == 3) {
        // Interior random (not endpoints)
        N = rnd.next(2, 10);
    } else {
        // Fully random
        N = rnd.next(1, 11);
    }

    println(N);
    return 0;
}
