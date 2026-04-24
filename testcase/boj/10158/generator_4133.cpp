#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to choose size regime
    int regime = rnd.next(0, 2);
    int w, h, t_bound;
    if (regime == 0) {
        // small grid, very short time
        w = rnd.next(2, 5);
        h = rnd.next(2, 5);
        t_bound = rnd.next(1, 5);
    } else if (regime == 1) {
        // medium grid, moderate time
        w = rnd.next(2, 10);
        h = rnd.next(2, 10);
        t_bound = rnd.next(5, 20);
    } else {
        // larger small grid, longer time
        w = rnd.next(5, 10);
        h = rnd.next(5, 10);
        t_bound = rnd.next(10, 30);
    }

    // initial position must be strictly inside
    int p = rnd.next(1, w - 1);
    int q = rnd.next(1, h - 1);

    // time to simulate
    int t = rnd.next(1, t_bound);

    // output in problem format
    println(w, h);
    println(p, q);
    println(t);

    return 0;
}
