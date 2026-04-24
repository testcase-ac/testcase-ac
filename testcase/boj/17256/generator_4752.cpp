#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> tvals = {-2, -1, 1, 2};

    // Sample cake number a = (ax, ay, az) with weighted randomness
    int ax = rnd.wnext(99, rnd.any(tvals)) + 1;   // 1..99
    int ay = rnd.wnext(100, rnd.any(tvals)) + 1;  // 1..100
    int az = rnd.wnext(99, rnd.any(tvals)) + 1;   // 1..99

    // Determine bounds for b = (bx, by, bz) so that c stays ≤100
    int bx_max = 100 - az;    // ensures c.x = az + bx ≤ 100
    int by_max = 100 / ay;    // ensures c.y = ay * by ≤ 100
    int bz_max = 100 - ax;    // ensures c.z = ax + bz ≤ 100

    // Sample b with a mix of uniform and weighted distributions
    int bx = rnd.next(0,1)
        ? rnd.next(1, bx_max)
        : rnd.wnext(bx_max, rnd.any(tvals)) + 1;
    int by = rnd.next(0,1)
        ? rnd.next(1, by_max)
        : rnd.wnext(by_max, rnd.any(tvals)) + 1;
    int bz = rnd.next(0,1)
        ? rnd.next(1, bz_max)
        : rnd.wnext(bz_max, rnd.any(tvals)) + 1;

    // Compute c = a 🍰 b = (az+bx, ay*by, ax+bz)
    int cx = az + bx;
    int cy = ay * by;
    int cz = ax + bz;

    // Output the single test case
    println(ax, ay, az);
    println(cx, cy, cz);
    return 0;
}
