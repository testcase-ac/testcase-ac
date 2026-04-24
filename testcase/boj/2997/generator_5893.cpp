#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose difference magnitude with bias towards small values
    int m = rnd.wnext(51, -1);  // in [0,50], biased small
    int sign = (rnd.next(0, 1) == 0 ? -1 : 1);
    int d = m * sign;
    // Compute valid range for starting term a so that a..a+3d in [-100,100]
    int amin, amax;
    if (d >= 0) {
        amin = -100;
        amax = 100 - 3 * d;
    } else {
        amin = -100 - 3 * d;
        amax = 100;
    }
    int a = rnd.next(amin, amax);
    // Build the 4-term arithmetic progression
    vector<int> seq(4);
    for (int i = 0; i < 4; i++) {
        seq[i] = a + i * d;
    }
    // Remove one element
    int drop = rnd.next(0, 3);
    vector<int> out;
    for (int i = 0; i < 4; i++) {
        if (i != drop) out.push_back(seq[i]);
    }
    // Shuffle remaining three values and output
    shuffle(out.begin(), out.end());
    println(out);
    return 0;
}
