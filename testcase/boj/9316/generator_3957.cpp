#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for N
    int maxN = 10;
    // mode 0: smallest, mode 1: bias towards larger, mode 2: bias towards smaller
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // edge case: smallest N
        N = 1;
    } else if (mode == 1) {
        // bias towards larger values up to maxN
        N = rnd.wnext(maxN, 1) + 1;
    } else {
        // bias towards smaller values down to 1
        N = rnd.wnext(maxN, -1) + 1;
    }

    // Output the single integer N
    println(N);
    return 0;
}
