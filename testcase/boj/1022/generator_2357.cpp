/* generator code */
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small submatrix size: rows up to 4, columns up to 5 (<=20 cells)
    int dr = rnd.next(0, 3);  // r2 - r1
    int dc = rnd.next(0, 4);  // c2 - c1

    // Keep coordinates in a small range [-4,4]
    int r1_lo = -4, r1_hi = 4 - dr;
    int c1_lo = -4, c1_hi = 4 - dc;
    int r1 = rnd.next(r1_lo, r1_hi);
    int c1 = rnd.next(c1_lo, c1_hi);
    int r2 = r1 + dr;
    int c2 = c1 + dc;

    // Output a single test case
    println(r1, c1, r2, c2);

    return 0;
}
