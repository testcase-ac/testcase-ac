#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Bias T to test edge and middle values: negative for low, positive for high, zero for uniform
    vector<int> biases = {-2, -1, 0, 1, 2};
    int tBias = rnd.any(biases);
    int T = rnd.wnext(24, tBias); // generates 0..23 with bias
    int S = rnd.next(0, 1);       // 0 or 1
    println(T, S);
    return 0;
}
