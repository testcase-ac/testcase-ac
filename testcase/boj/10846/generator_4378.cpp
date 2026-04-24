#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for biasing N towards small or large
    int bias = rnd.any(vector<int>{-1, 0, 1});
    // rnd.wnext(10, bias) gives in [0,9], biased if bias != 0
    int rawN = rnd.wnext(10, bias);
    int N = rawN + 1;  // N in [1,10]

    // Choose A and B
    int A = rnd.next(1, N);
    int B = rnd.next(A, N);

    // Some bit-patterns to stress bitwise OR logic
    vector<int> patterns = {
        0, 1, 2, 3, 5, 7, 15, 31, 63, 127,
        255, 511, 1023, 1024, 2047, 4095, 65535
    };

    // Generate ages Y_i
    vector<int> Y(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next(0, 1) == 0) {
            // pick a special pattern
            Y[i] = rnd.any(patterns);
        } else {
            // or a small random value
            Y[i] = rnd.next(0, 255);
        }
    }

    // Optionally shuffle the ages for more diversity
    shuffle(Y.begin(), Y.end());

    // Output
    println(N, A, B);
    println(Y);

    return 0;
}
