#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose magnitude category by random roll
    double roll = rnd.next();
    int absK;
    if (roll < 0.1) {
        // smallest edge case
        absK = 1;
    } else if (roll < 0.3) {
        // small 1-digit
        absK = rnd.next(2, 9);
    } else if (roll < 0.6) {
        // medium 2-3 digits
        absK = rnd.next(10, 999);
    } else if (roll < 0.8) {
        // larger 4-5 digits
        absK = rnd.next(1000, 99999);
    } else {
        // skew towards large values up to 1e7
        absK = rnd.wnext(10000000, 1) + 1;  // yields 1..1e7
    }
    if (absK > 10000000) absK = 10000000;
    // random sign
    int sign = rnd.next(0, 1) ? 1 : -1;
    int k = absK * sign;
    // ensure non-zero
    if (k == 0) k = 1;
    println(k);
    return 0;
}
