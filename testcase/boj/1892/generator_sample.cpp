#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int K;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        N = rnd.next(1, 5);
        K = rnd.next(1, N);
    } else if (mode == 1) {
        N = rnd.next(1, 40);
        K = 1;
    } else if (mode == 2) {
        N = rnd.next(1, 40);
        K = N;
    } else if (mode == 3) {
        N = rnd.next(20, 40);
        K = rnd.next(max(1, N / 2 - 3), min(N, N / 2 + 3));
    } else if (mode == 4) {
        N = 40;
        K = rnd.next(1, N);
    } else {
        N = rnd.next(1, 40);
        K = rnd.next(1, N);
    }

    println(N, K);
    return 0;
}
