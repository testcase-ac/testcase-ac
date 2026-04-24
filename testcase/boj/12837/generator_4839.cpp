#include "testlib.h"
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N and Q for hand-checkability
    int N = rnd.next(2, 10);
    int Q = rnd.next(1, 20);
    // Probability to choose an update operation
    double updProb = rnd.next();
    vector<tuple<int,int,long long>> ops;
    int type2cnt = 0;
    for (int i = 0; i < Q; i++) {
        bool forceQuery = (i == Q - 1 && type2cnt == 0);
        bool isUpdate = !forceQuery && (rnd.next() < updProb);
        if (isUpdate) {
            int p = rnd.next(1, N);
            long long x;
            // Hyper-parameter: mix small and large updates
            if (rnd.next() < 0.7)
                x = rnd.next(-1000, 1000);
            else
                x = rnd.next(-2000000000, 2000000000);
            ops.emplace_back(1, p, x);
        } else {
            int p = rnd.next(1, N);
            int q = rnd.next(p, N);
            ops.emplace_back(2, p, q);
            type2cnt++;
        }
    }
    // Output
    println(N, Q);
    for (auto &tup : ops) {
        int t, p;
        long long v;
        tie(t, p, v) = tup;
        if (t == 1)
            println(1, p, v);
        else
            println(2, p, (int)v);
    }
    return 0;
}
