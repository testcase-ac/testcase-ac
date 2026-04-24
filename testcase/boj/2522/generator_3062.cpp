#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: choose an upper bound for N to allow small or maximal tests
    vector<int> maxOptions = {5, 10, 100};
    int maxN = rnd.any(maxOptions);

    // Choose a sampling mode for diversity: uniform, skewed high, skewed low
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // Uniform distribution
        N = rnd.next(1, maxN);
    } else if (mode == 1) {
        // Skew towards larger values
        N = rnd.wnext(maxN, +1) + 1;
    } else {
        // Skew towards smaller values
        N = rnd.wnext(maxN, -1) + 1;
    }

    // Output the single integer N
    println(N);
    return 0;
}
