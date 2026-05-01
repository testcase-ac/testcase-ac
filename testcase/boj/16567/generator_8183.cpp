#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N
    int N = rnd.next(1, 20);
    // Hyper-parameter for M: sometimes small, sometimes larger
    int M;
    if (rnd.next() < 0.5) M = rnd.next(1, N * 2 + 1);
    else M = rnd.next(max(1, N), N * 4 + 1);
    // Hyper-parameter for initial dirty density: extreme or random
    int initType = rnd.next(0, 2);
    double p;
    if (initType == 0) p = 0.0;
    else if (initType == 1) p = 1.0;
    else p = rnd.next(0.0, 1.0);
    // Build initial sequence
    vector<int> a(N);
    for (int i = 0; i < N; ++i)
        a[i] = (rnd.next() < p ? 1 : 0);
    // Hyper-parameter for query frequency
    int qType = rnd.next(0, 2);
    double qProb;
    if (qType == 0) qProb = 0.1;
    else if (qType == 1) qProb = 0.9;
    else qProb = rnd.next(0.0, 1.0);
    // Generate operations
    vector<pair<int,int>> ops;
    bool hasQuery = false;
    for (int j = 0; j < M; ++j) {
        bool isQuery;
        if (j == M - 1 && !hasQuery) {
            isQuery = true;
        } else {
            isQuery = (rnd.next() < qProb);
        }
        if (isQuery) {
            ops.emplace_back(0, 0);
            hasQuery = true;
        } else {
            int idx = rnd.next(1, N);
            ops.emplace_back(1, idx);
        }
    }
    // Output
    println(N, M);
    println(a);
    for (auto &op : ops) {
        if (op.first == 0) println(0);
        else println(1, op.second);
    }
    return 0;
}
