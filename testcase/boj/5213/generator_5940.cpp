#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: skew across small and medium sizes
    int mode = rnd.next(0, 3);
    int N;
    if (mode == 0) N = rnd.next(1, 2);
    else if (mode == 1) N = rnd.next(3, 5);
    else if (mode == 2) N = rnd.next(6, 8);
    else N = rnd.next(9, 10);

    // Compute total tiles: odd rows N, even rows N-1
    int bigRows = (N + 1) / 2;
    int smallRows = N / 2;
    int total = bigRows * N + smallRows * (N - 1);

    // Hyper-parameter for distribution of numbers
    // 0: uniform, 1: skew to small, 2: skew to large
    int distr = rnd.next(0, 2);

    println(N);
    for (int i = 1; i <= total; i++) {
        int A, B;
        if (distr == 0) {
            A = rnd.next(1, 6);
            B = rnd.next(1, 6);
        } else if (distr == 1) {
            // skew to smaller numbers
            A = rnd.wnext(6, -2) + 1;
            B = rnd.wnext(6, -2) + 1;
        } else {
            // skew to larger numbers
            A = rnd.wnext(6, 2) + 1;
            B = rnd.wnext(6, 2) + 1;
        }
        println(A, B);
    }
    return 0;
}
