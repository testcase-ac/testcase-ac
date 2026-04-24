#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // 20% chance to pick an edge-case
    if (rnd.next() < 0.2) {
        if (rnd.next() < 0.5)
            println(1, 2, 3);
        else
            println(1, 98, 99);
        return 0;
    }

    // Hyper-parameters for total distance between first and last kangaroo
    int min_tot = 2, max_tot = 98;
    vector<int> ts = {-1, 0, 1};
    int t1 = rnd.any(ts);
    int t2 = rnd.any(ts);

    // Total gap dist_tot = (C - A)
    int dist_tot = rnd.wnext(max_tot - min_tot + 1, t1) + min_tot;
    // Split dist_tot into two positive parts dist1 and dist2
    int dist1 = rnd.wnext(dist_tot - 1, t2) + 1;
    int dist2 = dist_tot - dist1;

    // Choose A so that C = A + dist_tot <= 99
    int A_max = 99 - dist_tot;
    int A = rnd.next(1, A_max);
    int B = A + dist1;
    int C = B + dist2;

    // Output the three positions
    println(A, B, C);

    return 0;
}
