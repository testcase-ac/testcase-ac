#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate N with some bias towards small and edge N=1
    int N;
    if (rnd.next() < 0.1) {
        N = 1;
    } else {
        int t = rnd.next() < 0.3 ? -1 : 1;
        N = rnd.wnext(20, t) + 1; // N in [1,21]
    }

    // Number of updates and queries, at least 1, at most 10 (or 2*N whichever smaller)
    int M = rnd.next(1, min(10, N * 2));
    int K = rnd.next(1, min(10, N * 2));

    // Initial array with small values to avoid overflow in sums
    vector<long long> arr(N);
    for (int i = 0; i < N; i++) {
        arr[i] = rnd.next(-1000, 1000);
    }

    // Prepare operations: type 1 = update, type 2 = range query
    struct Op { int type, b, c; };
    vector<Op> ops;

    // Updates: set position b to value c
    for (int i = 0; i < M; i++) {
        int pos = rnd.next(1, N);
        long long val = rnd.next(-1000, 1000);
        ops.push_back({1, pos, (int)val});
    }

    // Queries: sum from b to c
    for (int i = 0; i < K; i++) {
        int x = rnd.next(1, N);
        int y = rnd.next(1, N);
        int b = min(x, y), c = max(x, y);
        ops.push_back({2, b, c});
    }

    // Shuffle operations to mix updates and queries
    shuffle(ops.begin(), ops.end());

    // Output
    println(N, M, K);
    for (auto v : arr) {
        println(v);
    }
    for (auto &op : ops) {
        println(op.type, op.b, op.c);
    }

    return 0;
}
