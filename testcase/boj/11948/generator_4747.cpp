#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for range of the four science scores A-D
    int L = rnd.next(0, 50);
    int H = rnd.next(L, 100);
    // Weighted bias: -1 (toward low), 0 (uniform), +1 (toward high)
    int idx = rnd.next(0, 2);
    int t = (idx == 0 ? -1 : (idx == 1 ? 0 : 1));
    int A[4];
    for (int i = 0; i < 4; i++) {
        // rnd.wnext(hi, t) gives [0, hi-1] biased by t
        A[i] = rnd.wnext(H - L + 1, t) + L;
    }

    // Hyper-parameter for history/geography scores E-F
    int mode = rnd.next(0, 3);
    int E, F;
    if (mode == 0) {
        // both uniform full range
        E = rnd.next(0, 100);
        F = rnd.next(0, 100);
    } else if (mode == 1) {
        // one very high, one moderate
        if (rnd.next(0, 1) == 0) {
            E = rnd.next(80, 100);
            F = rnd.next(0, 80);
        } else {
            F = rnd.next(80, 100);
            E = rnd.next(0, 80);
        }
    } else if (mode == 2) {
        // both fairly high
        E = rnd.next(50, 100);
        F = rnd.next(50, 100);
    } else {
        // tie case
        int x = rnd.next(0, 100);
        E = x;
        F = x;
    }

    // Output exactly 6 lines as per problem statement
    for (int i = 0; i < 4; i++) println(A[i]);
    println(E);
    println(F);

    return 0;
}
