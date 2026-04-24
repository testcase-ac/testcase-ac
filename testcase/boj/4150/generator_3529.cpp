#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for distribution type
    int distType = rnd.next(0, 2);
    int N;
    if (distType == 0) {
        // Uniform in [1,20]
        N = rnd.next(1, 20);
    } else if (distType == 1) {
        // Bias toward larger N in [1,20]
        N = rnd.wnext(20, 2) + 1;
    } else {
        // Bias toward smaller N in [1,20]
        N = rnd.wnext(20, -2) + 1;
    }

    // Output a single test case: one integer N
    println(N);

    return 0;
}
