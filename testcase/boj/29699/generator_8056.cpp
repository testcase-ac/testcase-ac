#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate N in different regimes to catch corner cases and typical cases
    int type = rnd.next(0, 4);
    int N;
    switch (type) {
        case 0:
            // Minimum edge case
            N = 1;
            break;
        case 1:
            // Exactly one full cycle length
            N = 13;
            break;
        case 2:
            // Small N (but not 1 or 13)
            N = rnd.next(2, 20);
            break;
        case 3:
            // Medium N
            N = rnd.next(1000, 100000);
            break;
        case 4:
            // Large N
            N = rnd.next(100001, 1000000);
            break;
    }
    println(N);
    return 0;
}
