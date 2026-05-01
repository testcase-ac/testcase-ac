/* generator code */
#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LO = 2;
    const int HI = 100000;
    int A, B;

    // With some probability, pick the full range
    if (rnd.next() < 0.2) {
        A = LO;
        B = HI;
    } else {
        // Choose a weight parameter for biased sampling of B
        vector<int> weights = { -5, -2, 2, 5 };
        int t = rnd.any(weights);
        // rnd.wnext(HI, t) produces a number in [0, HI-1] (biased)
        // +1 shifts to [1, HI]; clamp to [2, HI]
        int b0 = rnd.wnext(HI, t) + 1;
        B = max(LO, min(HI, b0));

        // For A, either start at LO or pick uniformly up to B
        if (rnd.next() < 0.5) {
            A = LO;
        } else {
            A = rnd.next(LO, B);
        }
    }

    // Ensure A <= B
    if (A > B) swap(A, B);

    // Output one test case
    println(A, B);

    return 0;
}
