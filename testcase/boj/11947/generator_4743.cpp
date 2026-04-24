#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(5, 12);
    println(T);

    // Special boundary values: 10^k - 1 and 10^9
    vector<int> boundaries = {
        9, 99, 999, 9999, 99999,
        999999, 9999999, 99999999, 999999999,
        1000000000
    };

    for (int i = 0; i < T; i++) {
        // Choose a type for diversity
        int kind = rnd.next(0, 4);
        int N;
        if (kind == 0) {
            // Very small N (1 digit)
            N = rnd.next(1, 9);
        } else if (kind == 1) {
            // Small N up to 1e3
            N = rnd.next(1, 1000);
        } else if (kind == 2) {
            // Medium N up to 1e6
            N = rnd.next(1, 1000000);
        } else if (kind == 3) {
            // Large N up to 1e9
            N = rnd.next(1, 1000000000);
        } else {
            // Exactly a boundary
            N = rnd.any(boundaries);
        }
        println(N);
    }

    return 0;
}
