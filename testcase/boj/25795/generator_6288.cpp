#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: sometimes small, sometimes large, otherwise uniform
    double p = rnd.next();
    int N;
    if (p < 0.2) {
        N = rnd.wnext(15, -3) + 1;  // biased towards small N
    } else if (p < 0.4) {
        N = rnd.wnext(15, 3) + 1;   // biased towards large N
    } else {
        N = rnd.next(1, 15);        // uniform
    }

    // Hyper-parameters for a, b, c: include edge values and varied distributions
    auto genParam = [&]() {
        double q = rnd.next();
        if (q < 0.1) return 1;                       // minimal
        if (q < 0.2) return 99999;                   // near max
        if (q < 0.5) return rnd.wnext(99999, -2) + 1; // bias small
        if (q < 0.8) return rnd.wnext(99999, 2) + 1;  // bias large
        return rnd.next(1, 99999);                   // uniform
    };

    int a = genParam();
    int b = genParam();
    int c = genParam();

    println(N, a, b, c);
    return 0;
}
