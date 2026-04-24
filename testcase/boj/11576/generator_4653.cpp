#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for base A: uniform, small-biased, or large-biased
    int modeA = rnd.next(0, 2);
    int A;
    if (modeA == 0) {
        A = rnd.next(2, 30);
    } else if (modeA == 1) {
        A = rnd.wnext(29, -2) + 2;  // bias toward smaller bases
    } else {
        A = rnd.wnext(29, 2) + 2;   // bias toward larger bases
    }
    // Hyper-parameter for base B: similar
    int modeB = rnd.next(0, 2);
    int B;
    if (modeB == 0) {
        B = rnd.next(2, 30);
    } else if (modeB == 1) {
        B = rnd.wnext(29, -2) + 2;
    } else {
        B = rnd.wnext(29, 2) + 2;
    }
    // Hyper-parameter for the decimal value x: biased small, medium, or large
    int t = rnd.next(-2, 2);
    int x = rnd.wnext((1 << 20) - 1, t) + 1;  // in [1, 2^20-1]
    // Convert x into base-A digits
    int y = x;
    vector<int> digits;
    while (y > 0) {
        digits.push_back(y % A);
        y /= A;
    }
    reverse(digits.begin(), digits.end());
    int m = digits.size();
    // Output
    println(A, B);
    println(m);
    println(digits);
    return 0;
}
