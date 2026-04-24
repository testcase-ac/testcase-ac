#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for diverse N selection
    double mode = rnd.next();  // [0,1)
    int N;
    if (mode < 0.2) {
        // Minimum edge case
        N = 1;
    } else if (mode < 0.4) {
        // Maximum edge case
        N = 80;
    } else if (mode < 0.7) {
        // Small random N
        N = rnd.next(1, 10);
    } else if (mode < 0.9) {
        // Bias towards smaller values
        N = rnd.wnext(80, -1) + 1;  // wnext(80,-1) favors smaller numbers in [0,79]
    } else {
        // Bias towards larger values
        N = rnd.wnext(80, 1) + 1;   // wnext(80,1) favors larger numbers in [0,79]
    }

    // Output single integer N
    println(N);
    return 0;
}
