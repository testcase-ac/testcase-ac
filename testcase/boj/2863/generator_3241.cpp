#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generator for a value in [1,100] with bias
    auto gen_val = [&](int bias)->int {
        const int hi = 100;
        if (bias == 0) return rnd.next(1, hi);
        int v = rnd.wnext(hi, bias); // in [0,hi-1]
        return v + 1;
    };
    double p = rnd.next(); // for special cases
    int A, B, C, D;
    if (p < 0.1) {
        // All equal
        int v = rnd.next(1, 100);
        A = B = C = D = v;
    } else if (p < 0.2) {
        // Rows equal
        int v1 = rnd.next(1, 100);
        int v2 = rnd.next(1, 100);
        A = B = v1;
        C = D = v2;
    } else if (p < 0.3) {
        // Columns equal
        int v1 = rnd.next(1, 100);
        int v2 = rnd.next(1, 100);
        A = C = v1;
        B = D = v2;
    } else {
        // Fully random with weighted bias
        int bA = rnd.next(-3, 3);
        int bB = rnd.next(-3, 3);
        int bC = rnd.next(-3, 3);
        int bD = rnd.next(-3, 3);
        A = gen_val(bA);
        B = gen_val(bB);
        C = gen_val(bC);
        D = gen_val(bD);
    }
    // Output the test case
    println(A, B);
    println(C, D);
    return 0;
}
