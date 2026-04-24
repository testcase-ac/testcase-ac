#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small but diverse
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; i++) {
        // Hyper-parameter to decide N distribution
        double s = rnd.next();
        int N;
        if (s < 0.1) {
            // Guarantee some minimal edge cases
            N = 1;
        } else if (s > 0.95) {
            // Guarantee some maximal edge cases
            N = 1000;
        } else if (s < 0.6) {
            // Small N
            N = rnd.next(2, 20);
        } else if (s < 0.85) {
            // Medium N
            N = rnd.next(21, 200);
        } else {
            // Large N but not maximal
            N = rnd.next(201, 999);
        }
        println(N);
    }

    return 0;
}
