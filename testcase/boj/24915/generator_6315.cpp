#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for hand-verification
    int N = rnd.next(3, 20);
    int Q = rnd.next(N, 3 * N);
    // Define bounds for values
    int boundLow = rnd.next(-15, -5);
    int boundHigh = rnd.next(5, 15);
    // Hyper-parameter: sometimes make A roughly monotone with noise
    bool monotone = rnd.next(0, 1);
    vector<int> A(N);
    if (monotone) {
        int base = rnd.next(-10, 10);
        int diff = rnd.next(1, 5);
        for (int i = 0; i < N; i++)
            A[i] = base + i * diff + rnd.next(-2, 2);
    } else {
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(boundLow, boundHigh);
    }
    // Decide counts for queries and updates
    int minQ = 1, maxQ = min(Q, N);
    int qCnt = rnd.next(minQ, maxQ);
    int uCnt = Q - qCnt;
    // Build operations
    vector<tuple<int,int,int>> ops;
    // Updates
    for (int i = 0; i < uCnt; i++) {
        int xi = rnd.next(1, N);
        int yi = rnd.next(boundLow, boundHigh);
        ops.emplace_back(1, xi, yi);
    }
    // Queries
    for (int i = 0; i < qCnt; i++) {
        int li = rnd.next(1, N - 2);
        int ri = rnd.next(li + 2, N);
        ops.emplace_back(2, li, ri);
    }
    // Shuffle operations to mix updates and queries
    shuffle(ops.begin(), ops.end());
    // Output
    println(N, Q);
    println(A);
    for (auto &op : ops) {
        int t, x, y;
        tie(t, x, y) = op;
        println(t, x, y);
    }
    return 0;
}
