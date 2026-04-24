#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter to bias N between 1 and 10
    vector<int> tNs = {-2, -1, 0, 1, 2};
    int tN = rnd.any(tNs);
    int N = rnd.wnext(10, tN) + 1;

    // Hyperparameter for A_i bounds
    vector<int> Bs = {10, 100, 1000};
    int B = rnd.any(Bs);

    // Generate the array A
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(-B, B);
    }

    // Determine number of queries M
    int maxQ = N * (N + 1) / 2;
    maxQ = min(maxQ, 20);
    int M = rnd.next(1, maxQ);

    // Generate queries with mixed uniform and length‐biased sampling
    vector<pair<int,int>> queries;
    queries.reserve(M);
    vector<int> tLs = {-1, 0, 1};
    for (int k = 0; k < M; k++) {
        if (rnd.next(2) == 0) {
            // Uniform pick of i, j
            int i = rnd.next(1, N);
            int j = rnd.next(i, N);
            queries.emplace_back(i, j);
        } else {
            // Biased by interval length
            int tL = rnd.any(tLs);
            int len = rnd.wnext(N, tL) + 1;  // length in [1..N]
            int i = rnd.next(1, N - len + 1);
            int j = i + len - 1;
            queries.emplace_back(i, j);
        }
    }

    // Output
    println(N);
    println(A);
    println(M);
    for (auto &q : queries) {
        println(q.first, q.second);
    }

    return 0;
}
