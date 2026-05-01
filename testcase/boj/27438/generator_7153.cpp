#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters to cover edge cases and varied sizes
    double r = rnd.next(0.0, 1.0);
    int N;
    if (r < 0.05) {
        // smallest possible
        N = 1;
    } else if (r < 0.10) {
        // largest possible
        N = 13559699;
    } else if (r < 0.30) {
        // small N for trivial checks
        N = rnd.next(2, 10);
    } else if (r < 0.60) {
        // medium N
        N = rnd.next(11, 1000);
    } else if (r < 0.90) {
        // large N
        N = rnd.next(1001, 1000000);
    } else {
        // very large N
        N = rnd.next(1000001, 13559698);
    }

    println(N);
    return 0;
}
