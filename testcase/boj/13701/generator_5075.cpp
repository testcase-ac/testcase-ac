#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);                // number of integers
    int rangeExp = rnd.next(4, 12);         // exponent for max value
    int maxVal = (1 << rangeExp) - 1;       // Ai in [0, maxVal]
    double dupProb = rnd.next();            // probability to repeat a previous value

    vector<int> a;
    a.reserve(N);
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < dupProb) {
            // pick a duplicate from already generated values
            a.push_back(rnd.any(a));
        } else {
            // generate a fresh value with optional bias using wnext
            int t = rnd.next(-2, 2);
            int v = rnd.wnext(maxVal + 1, t);
            a.push_back(v);
        }
    }

    // Output the sequence on one line
    println(a);

    return 0;
}
