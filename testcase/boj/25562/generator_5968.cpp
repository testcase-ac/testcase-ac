#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Bias towards small, uniform, or large N for variability
    vector<int> biases = {-1, 0, 1};
    int bias = rnd.any(biases);
    // rnd.wnext(29, bias) gives [0,28], biased; +2 -> N in [2,30]
    int N = rnd.wnext(29, bias) + 2;
    println(N);
    return 0;
}
