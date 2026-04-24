#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for hand-checking
    int T = rnd.next(1, 5);
    println(T);

    for (int ti = 0; ti < T; ti++) {
        // Hyper-parameter to include edge and varied sizes
        int choice = rnd.next(0, 9);
        int N;
        if (choice == 0) {
            // minimal edge case
            N = 1;
        } else if (choice == 1) {
            // maximal edge case
            N = 100;
        } else if (choice <= 4) {
            // small
            N = rnd.next(1, 10);
        } else if (choice <= 7) {
            // mid
            N = rnd.next(10, 50);
        } else {
            // large
            N = rnd.next(50, 100);
        }

        println(N);
    }

    return 0;
}
