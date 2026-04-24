#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity: bias toward small or large sizes
    vector<int> biases = {-2, -1, 0, 1, 2};
    int tM = rnd.any(biases);
    int tN = rnd.any(biases);

    // Generate M, N in [2..10] with weighted randomness
    int M = rnd.wnext(9, tM) + 2;
    int N = rnd.wnext(9, tN) + 2;

    // Output the test case
    println(M, N);

    return 0;
}
