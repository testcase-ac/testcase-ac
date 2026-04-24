#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose between small, medium, and large cases
    int mode = rnd.next(0, 2);
    int n;
    if (mode == 0) {
        // small edge cases
        n = rnd.any(vector<int>{1, 2, 3, 5, 10});
    } else if (mode == 1) {
        // moderate sizes
        n = rnd.next(11, 1000);
    } else {
        // large sizes, biased towards the upper bound
        // rnd.wnext(100000,3) gives max of 4 samples in [0,99999]
        n = rnd.wnext(100000, 3) + 1;
    }
    println(n);
    return 0;
}
