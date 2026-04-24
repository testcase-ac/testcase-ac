#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rings
    int N = rnd.next(3, 10);

    // Choose the first ring radius with three size categories
    int firstType = rnd.next(0, 2);
    int R1;
    if (firstType == 0) {
        R1 = rnd.next(1, 10);
    } else if (firstType == 1) {
        R1 = rnd.next(10, 100);
    } else {
        R1 = rnd.next(100, 1000);
    }

    // Precompute divisors of R1 for case of picking divisors
    vector<int> divisors;
    for (int d = 1; d * d <= R1; ++d) {
        if (R1 % d == 0) {
            divisors.push_back(d);
            if (d * d != R1) divisors.push_back(R1 / d);
        }
    }
    // Shuffle divisors to spread choices
    shuffle(divisors.begin(), divisors.end());

    // Build all radii
    vector<int> radii;
    radii.push_back(R1);
    for (int i = 2; i <= N; ++i) {
        int pick = rnd.next(0, 2);
        int Ri;
        if (pick == 0 && !divisors.empty()) {
            // pick a divisor of R1
            Ri = rnd.any(divisors);
        } else if (pick == 1) {
            // pick a multiple of R1 (if possible)
            int maxMult = 1000 / R1;
            if (maxMult >= 2) {
                int m = rnd.next(2, maxMult);
                Ri = R1 * m;
            } else {
                // fallback to random
                Ri = rnd.next(1, 1000);
            }
        } else {
            // completely random
            Ri = rnd.next(1, 1000);
        }
        radii.push_back(Ri);
    }

    // Output the generated test
    println(N);
    println(radii);

    return 0;
}
