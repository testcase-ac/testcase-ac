#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Weight parameter to bias N towards small or large
    vector<int> ts = {-3, -2, -1, 1, 2, 3};
    int t = rnd.any(ts);
    // Generate N in [1..10] with weighting
    int N = rnd.wnext(10, t) + 1;
    if (N < 1) N = 1;
    // k in [1..N*N]
    int k = rnd.next(1, N * N);
    println(N);
    println(k);
    return 0;
}
