#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of test cases
    int T = rnd.next(1, 20);
    println(T);

    const int MAXV = 1000000;
    for (int i = 0; i < T; i++) {
        // four types of intervals for diversity
        int type = rnd.next(0, 3);
        int N, M;
        if (type == 0) {
            // single point interval
            M = rnd.wnext(MAXV + 1, -2);  // bias to smaller values
            N = M;
        } else if (type == 1) {
            // small local range
            N = rnd.next(0, 100);
            M = N + rnd.next(0, 100);
        } else if (type == 2) {
            // range from 0 to M
            N = 0;
            M = rnd.wnext(MAXV + 1, -1);  // mild bias to smaller
        } else {
            // general random range, sometimes skewed high or low
            int A = (rnd.next(0, 1) == 0 ? rnd.wnext(MAXV + 1, 2)
                                        : rnd.wnext(MAXV + 1, -2));
            int B = (rnd.next(0, 1) == 0 ? rnd.wnext(MAXV + 1, 2)
                                        : rnd.wnext(MAXV + 1, -2));
            if (A <= B) {
                N = A; M = B;
            } else {
                N = B; M = A;
            }
        }
        // clamp just in case
        if (M > MAXV) M = MAXV;
        if (N > M) N = M;
        println(N, M);
    }

    return 0;
}
