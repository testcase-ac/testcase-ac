#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of test cases
    int T;
    int ttype = rnd.next(1, 3);
    if (ttype == 1) {
        T = rnd.next(1, 3);        // few cases
    } else if (ttype == 2) {
        T = rnd.next(4, 7);        // medium number of cases
    } else {
        T = rnd.next(8, 10);       // many small cases
    }

    vector<int> cases;
    cases.reserve(T);
    for (int i = 0; i < T; i++) {
        // Hyper-parameter for range of n
        double p = rnd.next();
        int lo, hi;
        if (p < 0.4) {
            lo = 6; hi = 20;         // small evens
        } else if (p < 0.7) {
            lo = 22; hi = 50;        // medium evens
        } else {
            lo = 52; hi = 100;       // larger evens
        }
        // generate even n in [lo,hi]
        int lo2 = (lo + 1) / 2;
        int hi2 = hi / 2;
        int k = rnd.next(lo2, hi2);
        int n = 2 * k;
        cases.push_back(n);
    }

    // Randomize order of cases
    shuffle(cases.begin(), cases.end());

    // Output cases one per line, then termination 0
    for (int n : cases) {
        println(n);
    }
    println(0);

    return 0;
}
