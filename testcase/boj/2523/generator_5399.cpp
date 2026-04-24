#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Maximum N for small, hand-checkable output
    const int MAXN = 10;
    // Choose distribution type: 0 = uniform, 1 = skew low, 2 = skew high
    int distType = rnd.next(0, 2);
    int N;
    if (distType == 0) {
        // Uniform distribution over [1, MAXN]
        N = rnd.next(1, MAXN);
    } else if (distType == 1) {
        // Skewed towards smaller values
        // rnd.wnext(MAXN, -2) gives a bias towards minimum of 3 samples
        N = rnd.wnext(MAXN, -2) + 1;
    } else {
        // Skewed towards larger values
        // rnd.wnext(MAXN, 2) gives a bias towards maximum of 3 samples
        N = rnd.wnext(MAXN, 2) + 1;
    }
    // Output single integer N
    println(N);
    return 0;
}
