#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We need a single multiple of 3 between 3 and 3000.
    // Hyper-parameter: choose different size regimes.
    double p = rnd.next();  // in [0,1)
    int k;
    if (p < 0.4) {
        // small: 3 to 30
        k = rnd.next(1, 10);
    } else if (p < 0.7) {
        // medium: 33 to 300
        k = rnd.next(11, 100);
    } else if (p < 0.9) {
        // larger medium: 303 to 1500
        k = rnd.next(101, 500);
    } else if (p < 0.98) {
        // near big: 1503 to 3000
        k = rnd.next(501, 1000);
    } else {
        // extreme ends: either smallest or largest
        k = rnd.next(0, 1) == 0 ? 1 : 1000;
    }

    int n = 3 * k;
    // Ensure boundary adherence
    n = max(3, min(3000, n));

    println(n);
    return 0;
}
