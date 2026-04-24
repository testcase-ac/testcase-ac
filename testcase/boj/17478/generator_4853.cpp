#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diverse N: edge, small, medium, large
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        // smallest edge case
        N = 1;
    } else if (p < 0.2) {
        // largest edge case
        N = 50;
    } else if (p < 0.6) {
        // small values
        N = rnd.next(2, 10);
    } else {
        // medium-high values
        N = rnd.next(11, 49);
    }
    println(N);
    return 0;
}
