#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter to choose case type
    int t = rnd.next(0, 5);
    int k, n;
    switch (t) {
        // small k, small n
        case 0:
            k = rnd.next(1, 5);
            n = rnd.next(1, 10);
            break;
        // small k, large n
        case 1:
            k = rnd.next(1, 5);
            n = rnd.next(1000000, 1000000000);
            break;
        // large k, small n
        case 2:
            k = rnd.next(45, 50);
            n = rnd.next(1, 100);
            break;
        // large k, large n
        case 3:
            k = rnd.next(45, 50);
            n = rnd.next(1000000, 1000000000);
            break;
        // fully random
        case 4:
            k = rnd.next(1, 50);
            n = rnd.next(1, 1000000000);
            break;
        // edge case n = 1
        default:
            k = rnd.next(1, 50);
            n = 1;
            break;
    }
    println(k, n);
    return 0;
}
