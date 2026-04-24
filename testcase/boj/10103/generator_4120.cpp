#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of rounds
    int n = rnd.next(1, 10);
    // probability of a tie in each round
    double tieProb = rnd.next(0.0, 1.0);
    // shape: 0 = bias a high, 1 = bias b high, 2 = uniform
    int shape = rnd.next(0, 2);

    println(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        if (rnd.next() < tieProb) {
            // force a tie
            a = b = rnd.next(1, 6);
        } else {
            if (shape == 0) {
                // bias a towards higher values
                a = rnd.wnext(6, 2) + 1;
                b = rnd.next(1, 6);
            } else if (shape == 1) {
                // bias b towards higher values
                b = rnd.wnext(6, 2) + 1;
                a = rnd.next(1, 6);
            } else {
                // uniform distribution
                a = rnd.next(1, 6);
                b = rnd.next(1, 6);
            }
        }
        println(a, b);
    }
    return 0;
}
