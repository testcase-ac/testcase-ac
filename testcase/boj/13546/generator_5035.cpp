#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence size
    int N = rnd.next(1, 10);

    // Hyper-parameter to bias K (max value)
    int tK = rnd.next(-1, 1);
    int K = rnd.wnext(N, tK) + 1;  // in [1, N]

    // Generate array A with weighted bias on values
    int tA = rnd.next(-1, 1);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.wnext(K, tA) + 1;  // in [1, K]
    }

    // Number of queries, capped for hand-checkability
    int maxM = min(N * (N + 1) / 2, 20);
    int tM = rnd.next(-1, 1);
    int M = rnd.wnext(maxM, tM) + 1;  // at least 1

    // Generate diverse queries
    vector<pair<int,int>> qs;
    qs.reserve(M);
    for (int i = 0; i < M; i++) {
        double p = rnd.next();
        int l, r;
        if (p < 0.2) {
            // point query
            l = rnd.next(1, N);
            r = l;
        } else if (p < 0.5) {
            // small segment
            int len = rnd.next(1, N);
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else {
            // general segment
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
        qs.emplace_back(l, r);
    }
    shuffle(qs.begin(), qs.end());

    // Output
    println(N, K);
    println(A);
    println(M);
    for (auto &qr : qs)
        println(qr.first, qr.second);

    return 0;
}
