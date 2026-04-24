#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate radius R with diverse distributions to catch edge cases
    int t = rnd.next(0, 5);
    int R;
    if (t == 0) {
        // minimal radius
        R = 1;
    } else if (t == 1) {
        // small radius
        R = rnd.next(2, 10);
    } else if (t == 2) {
        // medium radius
        R = rnd.next(11, 1000);
    } else if (t == 3) {
        // near maximum radius
        R = rnd.next(9900, 10000);
    } else if (t == 4) {
        // skewed toward small values
        R = rnd.wnext(10000, -1) + 1;
    } else {
        // skewed toward large values
        R = rnd.wnext(10000, 1) + 1;
    }
    println(R);
    return 0;
}
