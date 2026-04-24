#include "testlib.h"
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(2, 10);
    int M = rnd.next(1, min(20, N * 2));
    double p_flip = rnd.next(0.0, 1.0);
    string bias = rnd.next("small|large|random");

    // Output N and M
    println(N, M);

    // Generate M operations
    for (int i = 0; i < M; i++) {
        // Operation type: 0 = flip, 1 = count
        int O = (rnd.next() < p_flip ? 0 : 1);

        // Choose segment length based on bias
        int length;
        if (bias == "small") {
            // Bias toward small segments
            length = rnd.wnext(N, -2) + 1;
        } else if (bias == "large") {
            // Bias toward large segments
            length = rnd.wnext(N, 2) + 1;
        } else {
            // Uniform segments
            length = rnd.next(1, N);
        }
        length = min(length, N);

        // Choose a valid [l, r] with r = l + length - 1
        int l = rnd.next(1, N - length + 1);
        int r = l + length - 1;

        // Print the operation
        println(O, l, r);
    }

    return 0;
}
