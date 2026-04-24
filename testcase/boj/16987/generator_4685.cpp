#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of eggs between 1 and 8
    int N = rnd.next(1, 8);
    // Choose a pattern to diversify test cases
    int pattern = rnd.next(0, 3);
    println(N);
    for (int i = 0; i < N; i++) {
        int S, W;
        if (pattern == 0) {
            // Heavy weights, low durability
            W = rnd.next(200, 300);
            S = rnd.next(1, 100);
        } else if (pattern == 1) {
            // High durability, low weight
            S = rnd.next(200, 300);
            W = rnd.next(1, 100);
        } else if (pattern == 2) {
            // Fully random
            S = rnd.next(1, 300);
            W = rnd.next(1, 300);
        } else {
            // Alternate heavy and strong
            if (i % 2 == 0) {
                W = rnd.next(200, 300);
                S = rnd.next(1, 100);
            } else {
                S = rnd.next(200, 300);
                W = rnd.next(1, 100);
            }
        }
        println(S, W);
    }
    return 0;
}
