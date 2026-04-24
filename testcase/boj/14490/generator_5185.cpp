#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small primes for hyper-parameters
    vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

    // Choose a scenario
    int scenario = rnd.next(0, 3);
    int n, m;

    if (scenario == 0) {
        // identical numbers
        int x = rnd.any(primes);
        n = x;
        m = x;
    }
    else if (scenario == 1) {
        // co-prime numbers
        do {
            n = rnd.next(1, 100);
            m = rnd.next(1, 100);
        } while (gcd(n, m) != 1);
    }
    else if (scenario == 2) {
        // one is a multiple of the other
        m = rnd.next(1, 50);
        int k = rnd.next(2, 10);
        n = m * k;
    }
    else {
        // general pair with non-trivial gcd
        int g = rnd.any(primes);
        int a = rnd.next(1, 50);
        int b = rnd.next(1, 50);
        n = g * a;
        m = g * b;
    }

    // Ensure within problem limits
    n = min(n, 100000000);
    m = min(m, 100000000);

    // Output in the required format "n:m"
    printf("%d:%d\n", n, m);
    return 0;
}
