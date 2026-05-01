#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Scenario selector:
    // 0: no solution (G = 1,2,4)
    // 1: exactly one solution (odd G > 1)
    // 2: exactly two solutions (product of two distinct odd primes)
    // 3: multiple solutions (>=3)
    int scenario = rnd.next(0, 3);
    int G = 0;

    if (scenario == 0) {
        vector<int> noSol = {1, 2, 4};
        G = rnd.any(noSol);
    }
    else if (scenario == 1) {
        // generate an odd G in [3, 99999]
        int x = rnd.next(1, 49999);
        G = 2 * x + 1;
    }
    else if (scenario == 2) {
        // exactly two solutions: small products of two distinct odd primes
        vector<int> twoSol = {15, 21, 33, 35, 39, 51, 55, 57, 65, 77};
        G = rnd.any(twoSol);
    }
    else {
        // multiple solutions: 3-solution or 4-solution cases
        if (rnd.next(0, 1) == 0) {
            // exactly 3 solutions
            vector<int> threeSol = {45, 63, 75, 99};
            G = rnd.any(threeSol);
        } else {
            // exactly 4 solutions
            vector<int> fourSol = {105};
            G = rnd.any(fourSol);
        }
    }

    println(G);
    return 0;
}
