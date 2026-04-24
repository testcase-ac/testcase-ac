#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    double p = rnd.next();
    long long N;
    if (p < 0.1) {
        // explicit zero case
        N = 0;
    } else if (p < 0.3) {
        // small positive
        N = rnd.next(1, 20);
    } else if (p < 0.5) {
        // small negative
        N = -rnd.next(1, 20);
    } else if (p < 0.8) {
        // medium range, exclude zero
        do {
            N = rnd.next(-1000, 1000);
        } while (N == 0);
    } else if (p < 0.9) {
        // large random range, exclude zero
        do {
            N = rnd.next(-2000000000, 2000000000);
        } while (N == 0);
    } else {
        // extreme boundary
        vector<long long> bounds = {2000000000LL, -2000000000LL};
        N = rnd.any(bounds);
    }

    println(N);
    return 0;
}
