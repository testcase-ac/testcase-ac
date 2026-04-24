#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diverse S selection
    // We sometimes pick the smallest S=2, or small, medium, or large ranges.
    double p = rnd.next();
    int S;
    if (p < 0.1) {
        // Extreme small edge case
        S = 2;
    } else if (p < 0.3) {
        // Small range for hand-checkable
        S = rnd.next(3, 10);
    } else if (p < 0.6) {
        // Medium range
        S = rnd.next(11, 100);
    } else if (p < 0.9) {
        // Larger range
        S = rnd.next(101, 500);
    } else {
        // Maximal stress
        S = rnd.next(501, 1000);
    }

    println(S);
    return 0;
}
