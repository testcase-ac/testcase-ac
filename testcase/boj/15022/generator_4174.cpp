#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of teams and events
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 20);

    // Hyper-parameters for diversity
    double favProb = rnd.next(0.0, 1.0);        // probability an event is for team 1
    int penBias = rnd.next(-2, 2);              // bias for penalty distribution
    bool avoidStart = rnd.next(0, 1) == 1;      // whether to avoid team 1 at start
    int avoidLen = avoidStart ? rnd.next(1, m) : 0;

    // Output n and m
    println(n, m);

    // Generate events
    for (int i = 0; i < m; i++) {
        int t;
        if (n == 1) {
            t = 1;
        } else if (avoidStart && i < avoidLen) {
            // avoid favorite in the first avoidLen events
            t = rnd.next(2, n);
        } else if (rnd.next() < favProb) {
            t = 1;
        } else {
            t = rnd.next(2, n);
        }
        int p = rnd.wnext(1000, penBias) + 1; // penalty in [1,1000] with bias
        println(t, p);
    }

    return 0;
}
