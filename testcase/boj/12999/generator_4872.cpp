#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of houses
    int N = rnd.next(1, 10);
    // Maximum possible distinct intervals is N*(N+1)/2, cap Q to small for hand-checkable
    int maxQ = N * (N + 1) / 2;
    int Q = rnd.next(1, min(maxQ, 15));
    // Brightness range hyper-parameter
    vector<int> ranges = {0, 1, 2, 3, 5, 10};
    int R = rnd.any(ranges);
    // Generate brightness values
    vector<int> P(N);
    if (R == 0) {
        for (int i = 0; i < N; i++)
            P[i] = 0;
    } else {
        for (int i = 0; i < N; i++)
            P[i] = rnd.next(-R, R);
    }
    // Probability to choose a small segment
    double smallProb = rnd.next(0.0, 1.0);
    vector<pair<int,int>> queries;
    queries.reserve(Q);
    for (int i = 0; i < Q; i++) {
        int X, Y;
        if (rnd.next() < smallProb) {
            // small segment of length up to 3
            int len = rnd.next(1, min(N, 3));
            X = rnd.next(1, N - len + 1);
            Y = X + len - 1;
        } else {
            // arbitrary segment
            X = rnd.next(1, N);
            Y = rnd.next(X, N);
        }
        queries.emplace_back(X, Y);
    }
    // Output
    println(N, Q);
    println(P);
    for (auto &qr : queries)
        println(qr.first, qr.second);

    return 0;
}
