#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases: small for hand-checkable
    int T = rnd.next(1, 10);
    println(T);
    // Hyper-parameters for diversity of n
    double a = rnd.next(0.0, 1.0), b = rnd.next(0.0, 1.0), c = rnd.next(0.0, 1.0);
    double sum = a + b + c;
    if (sum < 1e-9) { a = b = c = 1.0; sum = 3.0; }
    double p_small = a / sum;
    double p_medium = b / sum;
    for (int i = 0; i < T; i++) {
        double x = rnd.next();
        int n;
        if (x < p_small) {
            // small n to catch edge cases
            n = rnd.next(1, 5);
        } else if (x < p_small + p_medium) {
            // medium n
            n = rnd.next(6, 20);
        } else {
            // large n near the upper bound
            n = rnd.next(21, 64);
        }
        println(n);
    }
    return 0;
}
