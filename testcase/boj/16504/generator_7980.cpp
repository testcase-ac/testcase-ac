#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a power-of-two size N = 2^m, with m from 1 to 5 (i.e., N in {2,4,8,16,32})
    int m = rnd.next(1, 5);
    int N = 1 << m;

    // Choose a value-distribution type for variety
    // 0: small [1,10], 1: medium [1,1000], 2: large [1,100000], 3: all ones, 4: all maxes
    int type = rnd.next(0, 4);
    int lo, hi;
    if (type == 0) { lo = 1; hi = 10; }
    else if (type == 1) { lo = 1; hi = 1000; }
    else if (type == 2) { lo = 1; hi = 100000; }
    else if (type == 3) { lo = 1; hi = 1; }
    else { lo = 100000; hi = 100000; }

    // Generate the grid
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rnd.next(lo, hi);
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(A[i]);
    }

    return 0;
}
