#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for hand-checking
    int C = rnd.next(1, 10);
    println(C);

    for (int i = 0; i < C; i++) {
        // Hyper-parameter to pick distribution of N
        int pick = rnd.next(0, 9);
        int N;
        if (pick == 0) {
            // edge case: minimum
            N = 1;
        } else if (pick == 1) {
            // edge case: maximum
            N = 1000;
        } else if (pick <= 5) {
            // small N
            N = rnd.next(2, 20);
        } else if (pick <= 8) {
            // medium N
            N = rnd.next(21, 200);
        } else {
            // large N
            N = rnd.next(201, 1000);
        }
        println(N);
    }

    return 0;
}
