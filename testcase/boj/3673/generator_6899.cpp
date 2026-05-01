#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int c = rnd.next(1, 3);
    println(c);
    for (int tc = 0; tc < c; tc++) {
        // Hyper-parameter for d: small edge, medium, large
        int dType = rnd.next(0, 2);
        int d;
        if (dType == 0) {
            d = 1;
        } else if (dType == 1) {
            d = rnd.next(2, 100);
        } else {
            d = rnd.next(1000, 1000000);
        }
        // n biased towards smaller sizes but up to 15
        int n = rnd.wnext(15, -1) + 1;
        vector<long long> a(n);
        // Pattern for array values to catch different mod behaviors
        int pat = rnd.next(0, 3);
        for (int i = 0; i < n; i++) {
            if (pat == 0) {
                // values in [1, d] to often align with d
                a[i] = rnd.next(1, d);
            } else if (pat == 1) {
                // small values in [1, min(100, d)]
                a[i] = rnd.next(1, min(100, d));
            } else if (pat == 2) {
                // all ones
                a[i] = 1;
            } else {
                // large random values
                a[i] = rnd.next(1, 1000000000);
            }
        }
        println(d, n);
        println(a);
    }
    return 0;
}
