#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dog behavior hyper-parameters
    int A = rnd.wnext(10, -1) + 1;    // attack length for dog1
    int B = rnd.wnext(10, -2) + 1;    // rest length for dog1
    int C = rnd.wnext(10,  1) + 1;    // attack length for dog2
    int D = rnd.next(1, 10);         // rest length for dog2

    int dog1Cycle = A + B;
    int dog2Cycle = C + D;
    int maxCyc = max(dog1Cycle, dog2Cycle);

    // Overall time range for arrivals
    int T_max = rnd.next(maxCyc, maxCyc * 3);

    // Generate arrival times with some on-cycle-boundaries
    auto genTime = [&]() {
        if (rnd.next() < 0.3) {
            vector<int> cycles = { dog1Cycle, dog2Cycle };
            int base = rnd.any(cycles);
            int k = rnd.next(1, 3);
            return base * k;
        } else {
            return rnd.next(1, T_max);
        }
    };

    int P = genTime();  // postman
    int M = genTime();  // milkman
    int N = genTime();  // newspaper deliverer

    // Output
    println(A, B, C, D);
    println(P, M, N);

    return 0;
}
