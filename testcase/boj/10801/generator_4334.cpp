#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Base deck 1..10
    vector<int> base(10);
    iota(base.begin(), base.end(), 1);

    // Hyper-parameter for A's permutation pattern
    int modeA = rnd.next(0, 3);
    vector<int> A;
    if (modeA == 0) {
        A = base;
        shuffle(A.begin(), A.end());
    } else if (modeA == 1) {
        A = base;  // sorted ascending
    } else if (modeA == 2) {
        A = base;
        reverse(A.begin(), A.end());  // sorted descending
    } else {
        A = base;
        int r = rnd.next(1, 9);
        rotate(A.begin(), A.begin() + r, A.end());  // rotated ascending
    }

    // Hyper-parameter for B's permutation relative to A
    int modeB = rnd.next(0, 2);
    vector<int> B;
    if (modeB == 0) {
        B = base;
        shuffle(B.begin(), B.end());
    } else if (modeB == 1) {
        B = A;  // same as A, all ties
    } else {
        B = A;
        reverse(B.begin(), B.end());  // reverse of A
    }

    // Output the test case: two lines of 10 cards each
    println(A);
    println(B);

    return 0;
}
