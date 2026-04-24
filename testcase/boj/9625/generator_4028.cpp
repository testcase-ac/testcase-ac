#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose distribution type for diversity
    // 0: uniform, 1: skewed to high K, 2: skewed to low K, 3: edge values
    int distType = rnd.next(0, 3);
    int K;
    if (distType == 0) {
        // uniform between 1 and 45
        K = rnd.next(1, 45);
    } else if (distType == 1) {
        // weighted maximum (skew high): many samples, take max
        K = rnd.wnext(45, 1) + 1;  // rnd.wnext gives [0,44]
    } else if (distType == 2) {
        // weighted minimum (skew low): many samples, take min
        K = rnd.wnext(45, -1) + 1; // rnd.wnext gives [0,44]
    } else {
        // force extreme edge cases
        vector<int> edges = {1, 45};
        K = rnd.any(edges);
    }

    // Output single integer K
    println(K);
    return 0;
}
