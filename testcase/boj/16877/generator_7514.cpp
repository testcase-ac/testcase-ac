#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of piles
    int N = rnd.next(1, 20);
    // Precompute Fibonacci numbers up to 3e6
    const int MAXP = 3000000;
    vector<int> fib;
    fib.push_back(1);
    fib.push_back(2);
    while (true) {
        int sz = fib.size();
        int nxt = fib[sz-1] + fib[sz-2];
        if (nxt > MAXP) break;
        fib.push_back(nxt);
    }
    // Hyper-parameters
    bool allEqual = rnd.next(0, 1);
    double fibFrac = rnd.next(); // fraction of piles that are exact Fibonacci
    vector<int> biases = {-2, 0, 2}; // negative: bias low, zero: uniform, positive: bias high
    int distBias = rnd.any(biases);

    vector<int> P(N);
    if (allEqual) {
        // All piles same size
        int val;
        if (rnd.next(0, 1) == 0) {
            // choose a random Fibonacci size
            val = rnd.any(fib);
        } else {
            // choose biased random size
            val = rnd.wnext(MAXP, distBias) + 1;
        }
        for (int i = 0; i < N; i++)
            P[i] = val;
    } else {
        for (int i = 0; i < N; i++) {
            if (rnd.next() < fibFrac) {
                // exact Fibonacci
                P[i] = rnd.any(fib);
            } else {
                // biased random
                P[i] = rnd.wnext(MAXP, distBias) + 1;
            }
        }
    }
    // Output
    println(N);
    println(P);
    return 0;
}
