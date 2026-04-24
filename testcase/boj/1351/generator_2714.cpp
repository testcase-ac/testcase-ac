#include "testlib.h"
using namespace std;

int randomParam() {
    double u = rnd.next();
    if (u < 0.3) return rnd.next(2, 5);
    else if (u < 0.6) return rnd.next(5, 20);
    else return rnd.next(10, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with some edge cases and ranges
    int caseType = rnd.next(1, 4);
    long long N;
    if (caseType == 1) {
        N = 0;
    } else if (caseType == 2) {
        N = 1;
    } else if (caseType == 3) {
        N = rnd.next(2, 20);
    } else {
        N = rnd.next(20, 100);
    }
    // Choose P and Q with diversity: some huge, some equal, some independent small
    int P, Q;
    double v = rnd.next();
    if (v < 0.2) {
        // large divisors
        P = rnd.next(1000000, 1000000000);
        Q = rnd.next(1000000, 1000000000);
    } else if (v < 0.4) {
        // equal small
        P = randomParam();
        Q = P;
    } else {
        // independent small/moderate
        P = randomParam();
        Q = randomParam();
    }
    // Output
    println(N, P, Q);
    return 0;
}
