#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias toward small or large via wnext
    int tN = rnd.next(-1, 2);               // distribution parameter
    int N = rnd.wnext(10, tN) + 1;          // N in [1..10]

    // Hyper-parameter for maximum lecture length
    vector<int> lenOptions = {10, 20, 50, 100};
    int hiLen = rnd.any(lenOptions);        // pick from options

    // Hyper-parameter for length distribution: positive t favors larger numbers, negative favors smaller
    int tLen = rnd.next(-2, 2);

    // Generate lecture lengths
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.wnext(hiLen, tLen) + 1;  // values in [1..hiLen]
    }

    // Optionally sort to create increasing or decreasing sequences
    int distType = rnd.next(0, 2);
    if (distType == 1) {
        sort(a.begin(), a.end());
    } else if (distType == 2) {
        sort(a.begin(), a.end(), greater<int>());
    }

    // Hyper-parameter for M: sometimes 1, sometimes N, otherwise random
    int distM = rnd.next(0, 2);
    int M;
    if (distM == 0) {
        M = 1;
    } else if (distM == 1) {
        M = N;
    } else {
        M = rnd.next(1, N);
    }

    // Output
    println(N, M);
    println(a);

    return 0;
}
