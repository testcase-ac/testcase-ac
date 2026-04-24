#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of intermediate stops: small but varied
    int N = (rnd.next() < 0.5 ? rnd.next(1, 3) : rnd.next(3, 10));
    // Starting passengers: biased small or sometimes large
    int K;
    if (rnd.next() < 0.7) {
        K = rnd.wnext(20, -1) + 1;  // [1,20] biased low
    } else {
        K = rnd.next(1, 10000);
    }
    println(N, K);
    int cur = K;
    for (int i = 0; i < N; i++) {
        // Occasionally a no-op stop
        if (rnd.next() < 0.1) {
            println(0, 0);
            continue;
        }
        // Compute max possible alighting within bounds
        int maxOff = min(cur, 10000);
        int B;
        // Occasionally unload to (nearly) empty
        if (cur > 0 && rnd.next() < 0.05) {
            B = maxOff;
        } else {
            B = (maxOff > 0 ? rnd.next(0, maxOff) : 0);
        }
        // Boarding: biased small or sometimes large
        int A;
        if (rnd.next() < 0.7) {
            A = rnd.wnext(21, -1);  // [0,20] biased low
        } else {
            A = rnd.next(0, 10000);
        }
        println(A, B);
        cur = cur - B + A;
    }
    return 0;
}
