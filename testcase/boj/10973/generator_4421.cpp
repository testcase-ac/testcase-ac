#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias towards small or large
    int tBias = rnd.any(vector<int>{-1, 1});
    int baseN = rnd.wnext(10, tBias); // in [0,9], biased
    int N = baseN + 1;               // in [1,10]

    // Build the initial permutation 1..N
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);

    // Hyper-parameter for mode: 0=ascending,1=descending,2=random (biased to random)
    int mode = rnd.wnext(3, 1); // values in [0,2], more often 2

    if (mode == 1) {
        // strictly descending
        reverse(perm.begin(), perm.end());
    } else if (mode == 2) {
        // random permutation but avoid pure ascending/descending when possible
        if (N >= 3) {
            do {
                shuffle(perm.begin(), perm.end());
            } while (is_sorted(perm.begin(), perm.end()) ||
                     is_sorted(perm.begin(), perm.end(), greater<int>()));
        } else {
            shuffle(perm.begin(), perm.end());
        }
    }
    // else mode==0: keep ascending

    // Output
    println(N);
    println(perm);

    return 0;
}
