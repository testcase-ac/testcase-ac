#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for variability
    int tw = rnd.next(-1, 1);
    int th = rnd.next(-1, 1);
    int w = rnd.wnext(9, tw) + 2; // width in [2,10], biased by tw
    int h = rnd.wnext(9, th) + 2; // height in [2,10], biased by th
    int sx = rnd.next(1, 100 - w);
    int sy = rnd.next(1, 100 - h);
    // Choose direction order: 0 = R U L D, 1 = U R D L
    int pattern = rnd.next(0, 1);
    println(sx, sy);
    println(4);
    if (pattern == 0) {
        println("R", w);
        println("U", h);
        println("L", w);
        println("D", h);
    } else {
        println("U", h);
        println("R", w);
        println("D", h);
        println("L", w);
    }
    return 0;
}
