#include "testlib.h"
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with small to medium sizes
    int N;
    double p = rnd.next();
    if (p < 0.3) N = rnd.next(3, 5);
    else if (p < 0.7) N = rnd.next(6, 8);
    else N = rnd.next(9, 10);

    // Choose M similarly
    int M;
    double q = rnd.next();
    if (q < 0.3) M = rnd.next(3, 5);
    else if (q < 0.7) M = rnd.next(6, 8);
    else M = rnd.next(9, 10);

    // Decide the upper bound for A[i][j]
    int valHigh = (rnd.next() < 0.5 ? 10 : 100);

    // Generate the array A
    vector<vector<int>> A(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = rnd.next(1, valHigh);
        }
    }

    // Choose K with a biased distribution
    int K;
    double r = rnd.next();
    if (r < 0.2) K = 1;
    else if (r < 0.5) K = rnd.next(2, 3);
    else if (r < 0.8) K = rnd.next(4, 5);
    else K = 6;

    // Maximum possible s so that the rotation fits: 1+s <= N-s and 1+s <= M-s
    int sMax = (min(N, M) - 1) / 2;  // ensures 2*s <= min(N,M)-1
    if (sMax < 1) sMax = 1;

    // Generate K rotation operations
    vector<tuple<int,int,int>> ops;
    for (int i = 0; i < K; i++) {
        // Choose s with some edge‐case bias
        double t = rnd.next();
        int s;
        if (t < 0.3) s = 1;
        else if (t < 0.6) s = sMax;
        else s = rnd.next(1, sMax);
        // Choose center (r,c) so that the square fits
        int rr = rnd.next(1 + s, N - s);
        int cc = rnd.next(1 + s, M - s);
        ops.emplace_back(rr, cc, s);
    }

    // Randomize the order of operations
    shuffle(ops.begin(), ops.end());

    // Output the test case
    println(N, M, K);
    for (auto &row : A) println(row);
    for (auto &op : ops) {
        int rr, cc, ss;
        tie(rr, cc, ss) = op;
        println(rr, cc, ss);
    }

    return 0;
}
