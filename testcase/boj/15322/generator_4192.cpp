#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int K = rnd.next(5, 10);
    println(K);

    for (int i = 0; i < K; ++i) {
        // Guarantee at least one trivial case
        if (i == 0) {
            println(1, 1);
            continue;
        }
        // Choose among several shapes for diversity
        int mode = rnd.next(0, 4);
        int N, M;
        if (mode == 0) {
            // One row
            N = 1;
            M = rnd.next(1, 15);
        } else if (mode == 1) {
            // One column
            M = 1;
            N = rnd.next(1, 15);
        } else if (mode == 2) {
            // Square
            N = rnd.next(2, 15);
            M = N;
        } else if (mode == 3) {
            // Wide rectangle
            N = rnd.next(2, 7);
            M = rnd.next(8, 15);
        } else {
            // Tall rectangle
            N = rnd.next(8, 15);
            M = rnd.next(2, 7);
        }
        println(N, M);
    }

    return 0;
}
