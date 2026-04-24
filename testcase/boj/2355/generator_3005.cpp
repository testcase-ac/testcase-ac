#include "testlib.h"
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A, B;
    // Three main scenario types for diversity
    int t = rnd.next(0, 2);
    if (t == 0) {
        // Small values around zero
        A = rnd.next(-10, 10);
        B = rnd.next(-10, 10);
    } else if (t == 1) {
        // Medium-range window around a random center
        int center = rnd.next(-1000000, 1000000);
        int len = rnd.next(0, 1000);
        if (rnd.next(0, 1) == 0) {
            A = center;
            B = center + len;
        } else {
            A = center + len;
            B = center;
        }
    } else {
        // Extreme cases
        if (rnd.next(0, 1) == 0) {
            // Symmetric around zero -> sum = 0
            int hi = INT_MAX;
            int K = rnd.wnext(hi, 1);
            A = -K;
            B = K;
        } else {
            // Single extreme value
            if (rnd.next(0, 1) == 0) {
                // Near INT_MAX
                int lo = INT_MAX - 100;
                A = rnd.next(lo, INT_MAX);
            } else {
                // Near INT_MIN
                int hi = INT_MIN + 100;
                A = rnd.next(INT_MIN, hi);
            }
            B = A;
        }
    }

    // Output the generated test case
    println(A, B);
    return 0;
}
