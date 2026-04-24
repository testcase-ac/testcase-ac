#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for uneven distributions
    vector<int> weights = {-2, -1, 0, 1, 2};
    int tR = rnd.any(weights);
    int tC = rnd.any(weights);
    int tA = rnd.any(weights);
    int tB = rnd.any(weights);

    // Generate R, C, A, B in [1,10] with various biases
    int R = rnd.wnext(10, tR) + 1;
    int C = rnd.wnext(10, tC) + 1;
    int A = rnd.wnext(10, tA) + 1;
    int B = rnd.wnext(10, tB) + 1;

    // Output the test case
    println(R, C);
    println(A, B);

    return 0;
}
