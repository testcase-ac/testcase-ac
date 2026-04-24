#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Size of vectors
        int n = rnd.next(1, 8);
        println(n);

        // Choose a bound for coordinates
        vector<int> bounds = {10, 100, 1000};
        int bound = rnd.any(bounds);

        // Choose distribution type: 0 = uniform, 1 = positive bias, 2 = negative bias
        int type1 = rnd.next(0, 2);
        int type2 = rnd.next(0, 2);

        int range = 2 * bound + 1; // values from -bound..bound

        // Generate vectors
        vector<int> v1(n), v2(n);
        for (int i = 0; i < n; i++) {
            if (type1 == 0) {
                v1[i] = rnd.next(-bound, bound);
            } else if (type1 == 1) {
                // positive bias
                v1[i] = rnd.wnext(range, 2) - bound;
            } else {
                // negative bias
                v1[i] = rnd.wnext(range, -2) - bound;
            }
            if (type2 == 0) {
                v2[i] = rnd.next(-bound, bound);
            } else if (type2 == 1) {
                v2[i] = rnd.wnext(range, 2) - bound;
            } else {
                v2[i] = rnd.wnext(range, -2) - bound;
            }
        }

        // Output the two vectors
        println(v1);
        println(v2);
    }

    return 0;
}
