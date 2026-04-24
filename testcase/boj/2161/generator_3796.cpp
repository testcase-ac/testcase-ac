#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to choose N diversely but keep it small for hand checking
    double r = rnd.next();
    int N;
    if (r < 0.1) {
        // Edge case: smallest input
        N = 1;
    } else if (r < 0.3) {
        // Small inputs to test basic behavior
        N = rnd.next(2, 4);
    } else {
        // Typical small case range
        N = rnd.next(5, 10);
    }

    // Output the single integer input
    println(N);
    return 0;
}
