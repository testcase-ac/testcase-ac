#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a mode for small/medium/large N
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // small permutations, easy to hand-check
        N = rnd.next(1, 2);
    } else if (mode == 1) {
        // medium size
        N = rnd.next(3, 5);
    } else {
        // larger size, up to the problem's limit
        N = rnd.next(6, 8);
    }

    // Output the single integer N
    println(N);
    return 0;
}
