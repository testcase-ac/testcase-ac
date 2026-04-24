#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Precompute powers of 10
    int p10[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

    // Choose a scenario for diversity
    int scenario = rnd.next(0, 3);
    int A, B, C, D;

    if (scenario == 0) {
        // All small numbers
        A = rnd.next(1, 100);
        B = rnd.next(1, 100);
        C = rnd.next(1, 100);
        D = rnd.next(1, 100);
    } else if (scenario == 1) {
        // B and D large with random digit lengths, A and C small
        A = rnd.next(1, 100);
        C = rnd.next(1, 100);
        int db = rnd.next(1, 6);
        int dd = rnd.next(1, 6);
        B = rnd.next(p10[db-1], p10[db] - 1);
        D = rnd.next(p10[dd-1], p10[dd] - 1);
    } else if (scenario == 2) {
        // B and D all 9's (like 9,99,999,...), A and C arbitrary
        int db = rnd.next(1, 6);
        int dd = rnd.next(1, 6);
        B = p10[db] - 1;
        D = p10[dd] - 1;
        A = rnd.next(1, 1000000);
        C = rnd.next(1, 1000000);
    } else {
        // All very small or all very large
        if (rnd.next(0, 1) == 0) {
            A = rnd.next(1, 10);
            B = rnd.next(1, 10);
            C = rnd.next(1, 10);
            D = rnd.next(1, 10);
        } else {
            A = rnd.next(900000, 1000000);
            B = rnd.next(900000, 1000000);
            C = rnd.next(900000, 1000000);
            D = rnd.next(900000, 1000000);
        }
    }

    // Finally, with some small probability, swap pairs to avoid positional biases
    if (rnd.next() < 0.2) {
        swap(A, C);
        swap(B, D);
    }

    // Output the four numbers
    println(A, B, C, D);
    return 0;
}
