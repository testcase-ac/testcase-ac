#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N;
    int K;

    if (mode == 0) {
        N = rnd.next(1, 12);
        K = 1;
    } else if (mode == 1) {
        N = rnd.next(1, 12);
        K = N;
    } else if (mode == 2) {
        N = rnd.next(2, 20);
        K = rnd.next(1, N);
    } else if (mode == 3) {
        N = rnd.next(50, 200);
        K = rnd.next(1, N);
    } else if (mode == 4) {
        N = rnd.next(900, 1000);
        K = rnd.next(1, N);
    } else {
        N = 1000;
        K = rnd.next(990, 1000);
    }

    println(N, K);
    return 0;
}
