#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N;
    // 20% chance to test a large edge, otherwise small for hand-checking
    if (rnd.next(0, 4) == 0) {
        // bias toward smaller large values but allow up to 100000
        N = rnd.wnext(100000, -2) + 1;
    } else {
        // small N for easy verification
        N = rnd.next(1, 10);
    }
    println(N);
    return 0;
}
