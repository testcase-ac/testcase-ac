#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in various scenarios for diversity
    int scenario = rnd.next(0, 4);
    int N;
    if (scenario == 0) {
        // small N: only single-digit numbers
        N = rnd.next(1, min(9, 50));
    } else if (scenario == 1) {
        // medium N: includes some two-digit but not too large
        N = rnd.next(10, min(20, 50));
    } else if (scenario == 2) {
        // large N but avoid the 50-edge
        N = rnd.next(21, 49);
    } else if (scenario == 3) {
        // extreme endpoints
        N = rnd.next(0, 1) ? 50 : 1;
    } else {
        // border case around the single-to-double-digit boundary
        N = rnd.next(0, 1) ? 10 : 9;
    }

    // Build a random permutation of [1..N]
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end());

    // Concatenate without spaces
    string s;
    for (int x : perm) {
        s += to_string(x);
    }

    // Output the single line
    println(s);

    return 0;
}
