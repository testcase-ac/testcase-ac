#include "testlib.h"
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for diversity: three modes: very small, small, and large edge-case
    int mode = rnd.next(0, 2);
    int A, B, C;
    if (mode == 0) {
        // Very small balances
        A = rnd.next(0, 5);
        B = rnd.next(0, 5);
        C = rnd.next(0, 5);
    } else if (mode == 1) {
        // Small but hand-checkable
        A = rnd.next(0, 20);
        B = rnd.next(0, 20);
        C = rnd.next(0, 20);
    } else {
        // Large values that can trigger potential overflow in wrong solutions
        A = rnd.next(1000000000 - 5, 1000000000);
        B = rnd.next(1000000000 - 5, 1000000000);
        C = rnd.next(1000000000, 1000000001);
    }

    // Output in the required format
    println(A, B);
    println(C);

    return 0;
}
