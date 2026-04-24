#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of baskets
    int N = rnd.next(1, 10);
    // Determine number of operations with a bias towards small or large M
    int maxM = min(10, N * 2);
    int m0 = (rnd.next() < 0.5 ? rnd.wnext(maxM, -1) : rnd.wnext(maxM, 1));
    int M = m0 + 1;

    vector<array<int,3>> ops;
    for (int it = 0; it < M; it++) {
        // Choose range length with bias to small or large
        int len0 = (rnd.next() < 0.5 ? rnd.wnext(N, -1) : rnd.wnext(N, 1));
        int len = len0 + 1;  // [1..N]
        // Choose i and j so that j - i + 1 = len
        int i = rnd.next(1, N - len + 1);
        int j = i + len - 1;
        // Choose pivot k in [i, j]
        int k = rnd.next(i, j);
        ops.push_back({i, j, k});
    }

    // Output
    println(N, M);
    for (auto &op : ops)
        println(op[0], op[1], op[2]);

    return 0;
}
