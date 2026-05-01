#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We will pick among several scenarios to expose edge cases and typical cases.
    int scenario = rnd.next(0, 5);
    int Xi, Pi; // Xi in [0,9999] represents x*100, Pi in [0,4999] represents p*100

    switch (scenario) {
        // No rebate, p arbitrary
        case 0:
            Xi = 0;
            Pi = rnd.next(0, 4999);
            break;
        // No winning probability, x arbitrary
        case 1:
            Xi = rnd.next(0, 9999);
            Pi = 0;
            break;
        // High rebate, mid-to-high win probability
        case 2:
            Xi = rnd.next(8000, 9999);   // x in [80.00,99.99]
            Pi = rnd.next(2000, 4999);   // p in [20.00,49.99]
            break;
        // Moderate rebate and win chance
        case 3:
            Xi = rnd.next(2000, 8000);   // x in [20.00,80.00]
            Pi = rnd.next(1000, 4000);   // p in [10.00,40.00]
            break;
        // Low rebate and low win chance
        case 4:
            Xi = rnd.next(0, 2000);      // x in [0.00,20.00]
            Pi = rnd.next(0, 500);       // p in [0.00,5.00]
            break;
        // Fully random
        default:
            Xi = rnd.next(0, 9999);
            Pi = rnd.next(0, 4999);
            break;
    }

    double x = Xi / 100.0;
    double p = Pi / 100.0;
    // Print with two decimal places (allowed by input spec)
    printf("%.2f %.2f\n", x, p);
    return 0;
}
