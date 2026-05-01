#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We generate a single test N in [1, 1e6]
    // with several categories to catch edge and typical cases.
    int type = rnd.next(0, 5);
    int N;
    if (type == 0) {
        // Smallest edge
        N = 1;
    } else if (type == 1) {
        // Small N to test simple cases
        N = rnd.next(2, 20);
    } else if (type == 2) {
        // Medium N
        N = rnd.next(21, 500);
    } else if (type == 3) {
        // Upper-medium N still valid
        N = rnd.next(501, 1022);
    } else if (type == 4) {
        // Boundary values around the total count
        vector<int> v = {1023, 1024};
        N = rnd.any(v);
    } else {
        // Large N beyond limit to force -1
        N = rnd.next(1025, 1000000);
    }

    println(N);
    return 0;
}
