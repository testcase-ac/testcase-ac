#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of queries
    int Q = rnd.next(1, 20);
    println(Q);

    // Probability to generate a power of two
    double p = rnd.next(0.0, 1.0);
    // Exponent bias parameters for wnext
    vector<int> tExp = {-2, -1, 0, 1, 2};

    for (int i = 0; i < Q; i++) {
        int a;
        if (rnd.next() < p) {
            // Generate a power of two: 2^e where e in [0..30] with biased distribution
            int t = rnd.any(tExp);
            int e = rnd.wnext(31, t);  // yields in [0,30]
            a = 1 << e;
        } else {
            // Generate a non-power of two, mixing small and large ranges
            while (true) {
                long long x;
                if (rnd.next() < 0.5) {
                    x = rnd.next(1LL, 100LL);
                } else {
                    x = rnd.next((1LL<<30) + 1, (1LL<<31) - 1);
                }
                if ((x & (x - 1)) != 0) {
                    a = int(x);
                    break;
                }
            }
        }
        println(a);
    }

    return 0;
}
