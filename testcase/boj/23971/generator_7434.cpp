#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter modes for H
    int modeH = rnd.next(3); // 0: small, 1: medium, 2: large
    int H;
    if (modeH == 0) {
        H = rnd.next(1, 10);
    } else if (modeH == 1) {
        H = rnd.next(10, 1000);
    } else {
        H = rnd.next(1000, 50000);
    }
    // Hyper-parameter modes for W
    int modeW = rnd.next(3);
    int W;
    if (modeW == 0) {
        W = rnd.next(1, 10);
    } else if (modeW == 1) {
        W = rnd.next(10, 1000);
    } else {
        W = rnd.next(1000, 50000);
    }
    // Hyper-parameter modes for N
    int modeN = rnd.next(3);
    int N;
    if (modeN == 0) {
        int maxN = H < 10 ? H : 10;
        N = rnd.next(1, maxN);
    } else if (modeN == 1) {
        N = rnd.next(1, H);
    } else {
        N = rnd.next(H, 50000);
    }
    // Hyper-parameter modes for M
    int modeM = rnd.next(3);
    int M;
    if (modeM == 0) {
        int maxM = W < 10 ? W : 10;
        M = rnd.next(1, maxM);
    } else if (modeM == 1) {
        M = rnd.next(1, W);
    } else {
        M = rnd.next(W, 50000);
    }
    // Output single test case
    println(H, W, N, M);
    return 0;
}
