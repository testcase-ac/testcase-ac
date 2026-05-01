#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Use different distributions to catch edge cases and typical cases
    double p = rnd.next();
    int N;
    if (p < 0.05) {
        // smallest edge
        N = 1;
    } else if (p < 0.1) {
        // largest edge
        N = 10000;
    } else if (p < 0.4) {
        // small values
        N = rnd.next(2, 10);
    } else if (p < 0.7) {
        // medium values
        N = rnd.next(11, 1000);
    } else {
        // larger but not maximum
        N = rnd.next(1001, 10000);
    }

    println(N);
    return 0;
}
