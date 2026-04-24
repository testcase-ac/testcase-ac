#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a mode for sampling N to get diverse cases:
    // 0: small N, 1 to 10
    // 1: large N, 90 to 100
    // 2: full range, 1 to 100
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(1, 10);
    } else if (mode == 1) {
        N = rnd.next(90, 100);
    } else {
        N = rnd.next(1, 100);
    }
    println(N);
    return 0;
}
