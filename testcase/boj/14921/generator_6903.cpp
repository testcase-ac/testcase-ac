#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size of array
    int N = rnd.next(2, 10);

    // Hyper-parameters for diversity
    // 0: uniform mix; 1: only positives and negatives; 2: many zeros
    int distType = rnd.next(0, 2);

    int k = 0, z = 0, p = 0;
    if (distType == 0) {
        // uniform random splits
        k = rnd.next(0, N);
        z = rnd.next(0, N - k);
        p = N - k - z;
    } else if (distType == 1) {
        // extremes: no zeros
        k = rnd.next(0, N);
        z = 0;
        p = N - k;
    } else {
        // heavy zeros
        int loZeros = max(1, N / 2);
        z = rnd.next(loZeros, N);
        k = rnd.next(0, N - z);
        p = N - z - k;
    }

    // Range scale hyperparameter: small or larger magnitudes
    bool smallRange = rnd.next(0, 1);
    int negLo = smallRange ? -50 : -1000;
    int negHi = -1;
    int posLo = 1;
    int posHi = smallRange ? 50 : 1000;

    vector<int> a;
    a.reserve(N);
    for (int i = 0; i < k; i++) {
        a.push_back(rnd.next(negLo, negHi));
    }
    for (int i = 0; i < z; i++) {
        a.push_back(0);
    }
    for (int i = 0; i < p; i++) {
        a.push_back(rnd.next(posLo, posHi));
    }
    sort(a.begin(), a.end());

    // Output
    println(N);
    println(a);

    return 0;
}
