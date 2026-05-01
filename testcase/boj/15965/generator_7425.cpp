#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose among various hyper-parameters to expose edge cases
    int mode = rnd.next(0, 7);
    int K;
    switch (mode) {
        case 0:
            // Minimum edge
            K = 1;
            break;
        case 1:
            // Maximum edge
            K = 500000;
            break;
        case 2:
            // Very small K
            K = rnd.next(2, 10);
            break;
        case 3:
            // Subtask1 range
            K = rnd.next(2, 5000);
            break;
        case 4:
            // Subtask2 range
            K = rnd.next(5001, 40000);
            break;
        case 5:
            // Upper half of full range
            K = rnd.next(40001, 500000);
            break;
        case 6:
            // Skewed towards high values
            K = rnd.wnext(500000, 3) + 1;
            break;
        case 7:
            // Skewed towards low values
            K = rnd.wnext(500000, -3) + 1;
            break;
    }
    println(K);
    return 0;
}
