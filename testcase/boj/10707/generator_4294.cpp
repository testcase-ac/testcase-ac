#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small vs full range
    bool small = rnd.next(0, 1);

    // X company rate A
    int A = rnd.next(1, small ? 20 : 10000);
    // Y company base fee B
    int B = rnd.next(1, small ? 100 : 10000);
    // Y company free threshold C
    int C = rnd.next(1, small ? 20 : 10000);
    // Y company extra per liter D
    int D = rnd.next(1, small ? 10 : 10000);

    // Total usage P: sometimes <=C (no extra), sometimes >C
    int maxP = small ? 50 : 10000;
    bool over = rnd.next(0, 1);
    int P;
    if (over && C < maxP) {
        // ensure P > C
        P = rnd.next(C + 1, maxP);
    } else {
        // P in [1, C]
        P = rnd.next(1, C);
    }

    // Output in required format
    println(A);
    println(B);
    println(C);
    println(D);
    println(P);

    return 0;
}
