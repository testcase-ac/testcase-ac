#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    // N biased larger, M biased smaller
    int N = rnd.wnext(10, 1) + 1;      // [1,10], skewed to high
    int M = rnd.wnext(10, -1) + 1;     // [1,10], skewed to low

    // Total operations Q
    int Qmax = rnd.next(1, 20);
    int Q = rnd.next(1, Qmax);

    // Ensure at least one query operation
    int type2Count = rnd.next(1, Q);
    int type1Count = Q - type2Count;

    // Build operation list and shuffle
    vector<int> ops;
    for (int i = 0; i < type1Count; i++) ops.push_back(1);
    for (int i = 0; i < type2Count; i++) ops.push_back(2);
    shuffle(ops.begin(), ops.end());

    // Output header
    println(N, M, Q);

    // Generate operations
    for (int op : ops) {
        if (op == 1) {
            // Plant seeds in a rectangle
            int x1 = rnd.next(1, N);
            int x2 = rnd.next(x1, N);
            int y1 = rnd.next(1, M);
            int y2 = rnd.next(y1, M);
            int d  = rnd.next(-100, 100);
            println(1, x1, y1, x2, y2, d);
        } else {
            // Query seed nutrition at a point
            int x = rnd.next(1, N);
            int y = rnd.next(1, M);
            println(2, x, y);
        }
    }

    return 0;
}
