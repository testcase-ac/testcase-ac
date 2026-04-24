#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to choose distribution of N
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // small N for hand-checkable cases
        N = rnd.next(1, 10);
    } else if (mode == 1) {
        // medium N
        N = rnd.next(10, 100);
    } else {
        // large N near constraint limit
        N = rnd.next(500, 1000);
    }

    // Output the single test-case
    println(N);

    return 0;
}
