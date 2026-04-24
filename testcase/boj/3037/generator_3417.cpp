#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: small-biased, large-biased, or uniform in [1,10]
    int typeN = rnd.next(0, 2);
    int N;
    if (typeN == 0) {
        // bias towards small N (min of two draws from [0..9])
        N = rnd.wnext(10, -1) + 1;
    } else if (typeN == 1) {
        // bias towards large N (max of two draws from [0..9])
        N = rnd.wnext(10, 1) + 1;
    } else {
        // uniform
        N = rnd.next(1, 10);
    }
    int maxC = N * (N - 1) / 2;
    // Hyper-parameter for C: low-biased, high-biased, or uniform in [0..maxC]
    int typeC = rnd.next(0, 2);
    int C;
    if (typeC == 0) {
        // bias towards small C
        C = rnd.wnext(maxC + 1, -1);
    } else if (typeC == 1) {
        // bias towards large C
        C = rnd.wnext(maxC + 1, 1);
    } else {
        // uniform
        C = rnd.next(0, maxC);
    }
    println(N, C);
    return 0;
}
