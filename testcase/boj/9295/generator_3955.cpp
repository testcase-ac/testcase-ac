#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small and hand-checkable
    int T = rnd.next(1, 10);
    println(T);

    for (int i = 0; i < T; ++i) {
        double p = rnd.next(); // for special-case injection
        int a, b;

        // Inject some edge rolls to catch formatting or boundary issues
        if (p < 0.1) {
            a = b = 1;        // both ones
        } else if (p < 0.2) {
            a = b = 6;        // both sixes
        } else if (p < 0.3) {
            a = 1; b = 6;     // min and max
        } else if (p < 0.4) {
            a = 6; b = 1;     // max and min
        } else {
            // Weighted bias hyper-parameter: t in [-2,2]
            int bias = rnd.next(-2, 2);
            a = rnd.wnext(6, bias) + 1; // dice roll from 1..6
            b = rnd.wnext(6, bias) + 1;
        }

        println(a, b);
    }

    return 0;
}
