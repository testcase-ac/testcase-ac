#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: between 1 and 25
    int t = rnd.next(1, 25);
    println(t);

    for (int i = 0; i < t; i++) {
        // Hyper-parameter for n: favor edge and mid cases
        int typeN = rnd.next(0, 4);
        int n;
        if (typeN == 0) {
            n = 1;               // smallest display count
        } else if (typeN == 1) {
            n = 9;               // largest display count
        } else if (typeN == 2) {
            n = rnd.next(2, 4);  // small mid-range
        } else if (typeN == 3) {
            n = rnd.next(5, 8);  // larger mid-range
        } else {
            n = rnd.next(1, 9);  // any valid
        }

        // Hyper-parameter for m: cover a wide range
        int typeM = rnd.next(0, 4);
        int m;
        if (typeM == 0) {
            m = 1;                    // trivial divisor
        } else if (typeM == 1) {
            m = rnd.next(2, 9);       // small
        } else if (typeM == 2) {
            m = rnd.next(10, 99);     // two-digit
        } else if (typeM == 3) {
            m = rnd.next(100, 9999);  // medium
        } else {
            m = rnd.next(10000, 100000); // large up to max
        }

        // Output one test case
        println(n, m);
    }

    return 0;
}
