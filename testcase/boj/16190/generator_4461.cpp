#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int n = rnd.next(1, 5);                 // number of up/down pairs
    int a0 = rnd.next(1, 5);                // starting x-coordinate
    int maxUp = rnd.next(1, 5);             // maximum upward delta
    // Build the a_i sequence
    vector<int> a;
    a.push_back(a0);
    int h = 0;  // current height

    for (int j = 1; j < 2*n; j++) {
        if (j % 2 == 1) {
            // upward segment (slope +1)
            int dx = rnd.next(1, maxUp);
            h += dx;
            a.push_back(a.back() + dx);
        } else {
            // downward segment (slope -1), cannot go below y=0
            int dx = rnd.next(1, h);
            h -= dx;
            a.push_back(a.back() + dx);
        }
    }

    // Choose house position x on the boundary between a0 and a[2n-1]
    int x = rnd.next(a.front(), a.back());

    // Output
    println(n);
    println(a);
    println(x);

    return 0;
}
