#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int n = rnd.next(1, 10);             // number of minutes
    int maxEntry = rnd.next(0, 20);      // upper bound for entries per minute
    int maxExit = rnd.next(0, 20);       // upper bound for exits per minute
    int m = rnd.next(0, 20);             // initial cars in tunnel
    bool enforceNoNeg = rnd.next(0, 1) == 0;
    int weightEntry = rnd.next(-2, 2);   // weighting for entry distribution
    int weightExit = rnd.next(-2, 2);    // weighting for exit distribution

    // Output n and initial m
    println(n);
    println(m);

    int current = m;
    for (int i = 0; i < n; i++) {
        // generate entries and exits with weighted or uniform distribution
        int enter = rnd.wnext(maxEntry + 1, weightEntry);
        int exitv = rnd.wnext(maxExit + 1, weightExit);
        if (enforceNoNeg) {
            // ensure we never drop below zero
            int maxPossibleExit = current + enter;
            if (exitv > maxPossibleExit) {
                exitv = rnd.next(0, maxPossibleExit);
            }
        }
        println(enter, exitv);
        current += enter - exitv;
    }
    return 0;
}
