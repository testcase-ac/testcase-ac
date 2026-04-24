#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Three modes for diverse N selection:
    // mode 0: uniform random in [1,30]
    // mode 1: weighted extremes via rnd.wnext
    // mode 2: pick from special small or max values
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 2) {
        vector<int> specials = {1, 2, 3, 30};
        N = rnd.any(specials);
    } else if (mode == 1) {
        // t > 0 biases towards larger N, t < 0 towards smaller N
        int t = rnd.next(-3, 3);
        N = rnd.wnext(30, t) + 1;  // rnd.wnext(30,t) gives [0..29]
    } else {
        N = rnd.next(1, 30);
    }

    // Output single test case
    println(N);
    return 0;
}
