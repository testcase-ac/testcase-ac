#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

bool isPrime(int x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0) return x == 2;
    for (int i = 3; i <= (int)sqrt(x); i += 2)
        if (x % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter t for biased sampling: negative -> small, positive -> large
    vector<int> tvals = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(tvals);

    // Mode: 0 = general, 1 = perfect square, 2 = prime
    int mode = rnd.next(0, 2);
    int n = 1;
    if (mode == 1) {
        // generate a perfect square <= 10000
        int x = rnd.next(1, 100);
        n = x * x;
    } else if (mode == 2) {
        // generate a prime <= 10000 via rejection
        do {
            n = rnd.wnext(10000, t) + 1;
        } while (!isPrime(n));
    } else {
        // general case, biased by wnext
        n = rnd.wnext(10000, t) + 1;
    }

    // Ensure constraints
    if (n < 1) n = 1;
    if (n > 10000) n = 10000;

    // Output
    println(n);
    return 0;
}
