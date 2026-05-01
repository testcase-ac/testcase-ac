#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for bias: negative t biases small, positive biases large
    vector<int> weights = {-5, -3, -1, 0, 1, 3, 5};
    int t = rnd.any(weights);

    // Generate n in [1,90] with weighted distribution
    int n = rnd.wnext(90, t) + 1;

    // Occasionally force a special edge-case value
    if (rnd.next(0, 9) == 0) {
        vector<int> special = {1, 2, 3, 10, 50, 89, 90};
        n = rnd.any(special);
    }

    // Output the single test-case
    println(n);
    return 0;
}
