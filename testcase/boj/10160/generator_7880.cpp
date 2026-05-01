#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose among different size scenarios for variability
    int scenario = rnd.next(1, 4);
    int N, K;
    switch (scenario) {
        case 1:
            // Edge case: minimum length, extreme K
            N = 5;
            K = rnd.any(vector<int>{3, 26});
            break;
        case 2:
            // Small password
            N = rnd.next(6, 50);
            K = rnd.next(3, 26);
            break;
        case 3:
            // Medium password, with K sometimes at extremes
            N = rnd.next(51, 1000);
            if (rnd.next(0, 2) == 0)
                K = 3;
            else if (rnd.next(0, 2) == 1)
                K = 26;
            else
                K = rnd.next(4, 25);
            break;
        case 4:
        default:
            // Large password to test performance
            N = rnd.next(100000, 1000000);
            K = rnd.next(3, 26);
            break;
    }

    // Output the test case
    println(N, K);
    return 0;
}
