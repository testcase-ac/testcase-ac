#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: small, medium, large
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(1, 5);
    } else if (mode == 1) {
        N = rnd.next(6, 10);
    } else {
        N = rnd.next(11, 20);
    }

    vector<int> L(N), J(N);
    for (int i = 0; i < N; i++) {
        // Cost distribution: zeros, small, medium, high
        int p = rnd.next(0, 9);
        if (p < 2) {
            L[i] = 0;
        } else if (p < 5) {
            L[i] = rnd.next(1, 10);
        } else if (p < 8) {
            L[i] = rnd.next(11, 50);
        } else {
            L[i] = rnd.next(51, 100);
        }
        // Joy distribution: zeros, small, medium, high
        p = rnd.next(0, 9);
        if (p < 2) {
            J[i] = 0;
        } else if (p < 4) {
            J[i] = rnd.next(1, 10);
        } else if (p < 8) {
            J[i] = rnd.next(11, 50);
        } else {
            J[i] = rnd.next(51, 100);
        }
    }

    println(N);
    println(L);
    println(J);

    return 0;
}
