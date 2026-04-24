#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int LOW = 1946;
    const int HIGH = 1000000;
    int maxOffset = HIGH - LOW;

    // Occasionally pick exact boundaries
    int edge = rnd.next(0, 19);
    int N;
    if (edge == 0) {
        N = LOW;
    } else if (edge == 1) {
        N = HIGH;
    } else {
        // Three distribution modes for diversity
        int mode = rnd.next(0, 2);
        int offset;
        if (mode == 0) {
            // Uniform in [0, maxOffset]
            offset = rnd.next(0, maxOffset);
        } else if (mode == 1) {
            // Bias towards lower offsets (years near 1946)
            offset = rnd.wnext(maxOffset + 1, -3);
        } else {
            // Bias towards higher offsets (years near 1e6)
            offset = rnd.wnext(maxOffset + 1, 3);
        }
        N = LOW + offset;
    }

    println(N);
    return 0;
}
