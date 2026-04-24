#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose generation method
    // 0: small random [1,10]
    // 1: medium random [11,100]
    // 2: special triangular or near-triangular numbers
    int method = rnd.next(0, 2);
    int N = 1;

    vector<int> specials = {1,2,3,4,5,6,10,15,21,28,36,45,55,66,78,91};
    // filter to <=100 (already are)
    if (method == 0) {
        N = rnd.next(1, 10);
    } else if (method == 1) {
        N = rnd.next(11, 100);
    } else {
        // pick a special or just above it
        int x = rnd.any(specials);
        if (rnd.next(0,1) == 0) {
            N = x;
        } else {
            // just above: x+1, ensure <=100
            N = min(x + 1, 100);
        }
    }

    // As a final tweak, with small probability bump into a round number
    if (rnd.next(0, 9) == 0) {
        vector<int> rounds = {7, 14, 21, 28, 36, 45, 55, 66, 78, 91};
        N = rnd.any(rounds);
    }

    println(N);
    return 0;
}
