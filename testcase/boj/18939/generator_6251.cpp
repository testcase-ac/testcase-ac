#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(3, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        int type = rnd.next(1, 4);
        int N, M, K;
        if (type == 1) {
            // Degenerate: single row
            N = 1;
            M = rnd.next(1, 100000);
            K = 1;
        } else if (type == 2) {
            // Square board, K = N
            N = rnd.next(1, 3000);
            M = N;
            K = N;
        } else if (type == 3) {
            // K = 1, arbitrary dimensions
            N = rnd.next(1, 3000);
            M = rnd.next(N, 100000);
            K = 1;
        } else {
            // General case: random N, M, and K biased to low/high
            N = rnd.next(1, 3000);
            M = rnd.next(N, 100000);
            int mid = (N + 1) / 2;
            if (rnd.next(0, 1) == 0)
                K = rnd.next(1, mid);
            else
                K = rnd.next(mid, N);
        }
        println(N, M, K);
    }
    return 0;
}
