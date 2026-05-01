#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of baskets
    int N = rnd.next(1, 10);
    // Number of swaps
    int M = rnd.next(1, 20);

    // Output N and M
    println(N, M);

    // Generate M swap operations
    for (int k = 0; k < M; k++) {
        int i, j;
        // With some probability, do a self-swap
        if (rnd.next() < 0.2) {
            i = rnd.next(1, N);
            j = i;
        } else {
            i = rnd.next(1, N);
            j = rnd.next(1, N);
            if (i > j) swap(i, j);
        }
        println(i, j);
    }

    return 0;
}
