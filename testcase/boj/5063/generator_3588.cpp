#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int N = rnd.next(1, 10);

    // Hyper-parameters for value ranges
    int r_lo = rnd.next(-20, 0);
    int r_hi = rnd.next(0, 20);
    int c_max = rnd.next(0, 20);
    int delta_max = rnd.next(1, 20);

    // We want all three outcomes: 0 => profit>r, 1 => profit==r, 2 => profit<r
    vector<int> types = {0, 1, 2};
    shuffle(types.begin(), types.end());

    // Output number of cases
    println(N);
    for (int i = 0; i < N; i++) {
        int type = (i < 3 ? types[i] : rnd.any(types));
        int r = rnd.next(r_lo, r_hi);
        int c = rnd.next(0, c_max);
        int e;
        if (type == 0) {
            // advertise: e - c > r
            int d = rnd.next(1, delta_max);
            e = r + c + d;
        } else if (type == 1) {
            // does not matter: e - c == r
            e = r + c;
        } else {
            // do not advertise: e - c < r
            int d = rnd.next(1, delta_max);
            e = r + c - d;
        }
        println(r, e, c);
    }

    return 0;
}
