#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide randomly whether to use uniform or weighted sampling
    bool useWeighted = rnd.next(0, 1) == 1;
    int A, B;

    if (useWeighted) {
        // Hyper-parameters tA and tB control bias: positive biases towards larger values,
        // negative towards smaller values.
        int tA = rnd.next(-2, 2);
        int tB = rnd.next(-2, 2);
        // rnd.wnext(9, t) generates a number in [0,9), so +1 to get [1,10), i.e., [1,9]
        A = rnd.wnext(9, tA) + 1;
        B = rnd.wnext(9, tB) + 1;
    } else {
        // Simple uniform sampling in [1,9]
        A = rnd.next(1, 9);
        B = rnd.next(1, 9);
    }

    // Output two integers A and B
    println(A, B);
    return 0;
}
