#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Op {
    int w, x1, y1, x2, y2;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for size
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);

    // Hyper-parameters for value ranges
    vector<int> vmax = {10, 100, 1000};
    int init_max = rnd.any(vmax);

    // Generate initial grid
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = rnd.next(1, init_max);

    // Probability of an update operation
    double updProb = rnd.next(0.0, 1.0);

    vector<Op> ops;
    int updCnt = 0, qCnt = 0;
    for (int i = 0; i < M; i++) {
        if (rnd.next() < updProb) {
            // update
            int x = rnd.next(1, N);
            int y = rnd.next(1, N);
            int cmax = rnd.any(vmax);
            int c = rnd.next(1, cmax);
            ops.push_back({0, x, y, c, 0});
            updCnt++;
        } else {
            // query
            int x1 = rnd.next(1, N);
            int x2 = rnd.next(x1, N);
            int y1 = rnd.next(1, N);
            int y2 = rnd.next(y1, N);
            ops.push_back({1, x1, y1, x2, y2});
            qCnt++;
        }
    }
    // Ensure at least one query (so there's some output)
    if (qCnt == 0 && M > 0) {
        int x1 = rnd.next(1, N);
        int x2 = rnd.next(x1, N);
        int y1 = rnd.next(1, N);
        int y2 = rnd.next(y1, N);
        ops[0] = {1, x1, y1, x2, y2};
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }
    for (auto &op : ops) {
        if (op.w == 0) {
            // update: w x y c
            println(op.w, op.x1, op.y1, op.x2);
        } else {
            // query: w x1 y1 x2 y2
            println(op.w, op.x1, op.y1, op.x2, op.y2);
        }
    }

    return 0;
}
