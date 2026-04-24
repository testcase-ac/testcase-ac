#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a generation style for diversity
    int style = rnd.next(0, 4);
    vector<int> p(4);

    auto gen = [&](int lo, int hi) {
        return rnd.next(lo, hi);
    };

    if (style == 0) {
        // All small values
        for (int i = 0; i < 4; i++) p[i] = gen(1, 5);
    } else if (style == 1) {
        // All large values near upper bound
        for (int i = 0; i < 4; i++) p[i] = gen(995, 1000);
    } else if (style == 2) {
        // Small seat rows, large seats per row
        p[0] = gen(1, 5);
        p[2] = gen(1, 5);
        p[1] = gen(995, 1000);
        p[3] = gen(995, 1000);
    } else if (style == 3) {
        // Large rows, small seats per row
        p[0] = gen(995, 1000);
        p[2] = gen(995, 1000);
        p[1] = gen(1, 5);
        p[3] = gen(1, 5);
    } else {
        // Fully random in the entire range
        for (int i = 0; i < 4; i++) p[i] = gen(1, 1000);
    }

    // Output: n1 k1 n2 k2
    println(p);
    return 0;
}
