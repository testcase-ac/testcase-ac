#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario type for diversity
    // 0: minimal case
    // 1: exact division case (O = (N-1)*k)
    // 2: near-equal split case with small remainder
    // 3: fully random valid case
    // 4: maximal N case
    int sc = rnd.next(0, 4);
    int N, O;

    if (sc == 0) {
        // Minimal N and minimal O
        N = 2;
        O = N;  // smallest valid remaining
    }
    else if (sc == 1) {
        // Exact division: M divisible by N, daughter takes M/N, so O = M - M/N = (N-1)*(M/N)
        N = rnd.next(3, 15);
        int maxk = 100 / (N - 1);
        if (maxk < 2) maxk = 2;
        int k = rnd.next(2, maxk);
        O = k * (N - 1);
    }
    else if (sc == 2) {
        // Near-equal split: M = k*N + r, 1 <= r < N, daughter takes floor(M/N)=k
        N = rnd.next(2, 15);
        int k = rnd.next(1, 5);
        int r = rnd.next(1, N - 1);
        O = k * (N - 1) + r;
    }
    else if (sc == 3) {
        // Fully random within [N,100]
        N = rnd.next(2, 15);
        O = rnd.next(N, 100);
    }
    else {
        // Maximal N
        N = 15;
        O = rnd.next(15, 100);
    }

    // Guarantee validity (should already hold)
    if (O < N) O = N;
    if (O > 100) O = 100;

    // Output the generated test
    println(N);
    println(O);

    return 0;
}
