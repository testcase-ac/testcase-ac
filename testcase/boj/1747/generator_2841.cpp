#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a category for N
    int cat = rnd.next(0, 3);
    int N;
    if (cat == 0) {
        // small N to get small palindromes
        N = rnd.next(1, 10);
    } else if (cat == 1) {
        // medium N to test typical range
        N = rnd.next(11, 1000);
    } else if (cat == 2) {
        // larger N but well below upper bound
        N = rnd.next(1001, 100000);
    } else {
        // near upper bound to test overflow beyond 1e6
        N = rnd.next(900000, 1000000);
    }

    // Occasionally force a special edge case
    if (rnd.next(0, 9) == 0) {
        vector<int> specials = {1, 2, 11, 101, 998990, 1000000};
        N = rnd.any(specials);
    }

    // Output the single integer N
    println(N);
    return 0;
}
