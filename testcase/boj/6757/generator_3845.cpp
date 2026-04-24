#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int X;
    // 5% chance to be the maximum possible value
    if (rnd.next(0, 19) == 0) {
        X = 1000000000;
    }
    // 10% chance to be the minimum possible value
    else if (rnd.next(0, 9) == 0) {
        X = 2;
    }
    else {
        // Three buckets for diverse sizes
        int bucket = rnd.next(0, 2);
        if (bucket == 0) {
            // Small values for hand checking
            X = rnd.next(3, 100);
        }
        else if (bucket == 1) {
            // Medium values
            X = rnd.next(101, 10000);
        }
        else {
            // Large but not max
            X = rnd.next(10001, 999999999);
        }
    }

    // Output the single test case
    println(X);
    return 0;
}
