#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases (excluding the terminating 0 0)
    int T = rnd.next(1, 10);

    // Hyper-parameters for distribution of cases
    double eqRate     = rnd.next(0.0, 1.0);
    double lessRate   = rnd.next(0.0, 1.0);
    double greaterRate= rnd.next(0.0, 1.0);
    double sumRates = eqRate + lessRate + greaterRate;
    if (sumRates == 0.0) {
        // avoid degenerate all-zero
        eqRate = 1.0;
        sumRates = 1.0;
    }

    for (int i = 0; i < T; i++) {
        double pick = rnd.next(0.0, 1.0) * sumRates;
        int a, b;
        if (pick < eqRate) {
            // equal case
            int coin = rnd.next(0, 2);
            if (coin == 0) {
                a = b = 1;
            } else if (coin == 1) {
                a = b = 1000000;
            } else {
                a = b = rnd.next(1, 1000000);
            }
        } else if (pick < eqRate + lessRate) {
            // a < b
            a = rnd.next(1, 999999);
            b = rnd.next(a + 1, 1000000);
        } else {
            // a > b
            b = rnd.next(1, 999999);
            a = rnd.next(b + 1, 1000000);
        }
        println(a, b);
    }

    // terminating line
    println(0, 0);

    return 0;
}
