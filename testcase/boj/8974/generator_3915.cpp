#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: pick one of several test types for diversity
    int type = rnd.next(1, 4);
    int A, B;

    if (type == 1) {
        // Small interval (length up to 10)
        int len = rnd.next(1, min(10, 1000));
        A = rnd.next(1, 1000 - len + 1);
        B = A + len - 1;
    } else if (type == 2) {
        // Full range
        A = 1;
        B = 1000;
    } else if (type == 3) {
        // Single element
        A = B = rnd.next(1, 1000);
    } else {
        // Completely random
        A = rnd.next(1, 1000);
        B = rnd.next(A, 1000);
    }

    // Output A and B
    println(A, B);

    return 0;
}
