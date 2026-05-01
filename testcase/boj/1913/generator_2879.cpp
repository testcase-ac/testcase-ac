#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: choose small odd between 3 and 11
    int r = rnd.next(1, 5);  // r in [1,5]
    int N = 2 * r + 1;       // N = 3,5,7,9,11

    // Hyper-parameter for X: sometimes pick special positions, else weighted random
    int X;
    double p = rnd.next();
    if (p < 0.1) {
        X = 1;                 // the center of the snail pattern
    } else if (p < 0.2) {
        X = N * N;             // the largest number
    } else if (p < 0.3) {
        X = (N * N + 1) / 2;   // mid-range value
    } else {
        int w = rnd.next(-2, 2);       // bias parameter
        X = rnd.wnext(N * N, w) + 1;   // weighted random in [1, N^2]
    }

    // Output in required format
    println(N);
    println(X);

    return 0;
}
