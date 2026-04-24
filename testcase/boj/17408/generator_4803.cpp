#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for sizes
    int N = rnd.next(2, 10);
    int M = rnd.next(2, 20);
    // Hyper-parameters for value ranges
    int vIniMax = rnd.next(5, 50);
    int vUpdMax = rnd.next(vIniMax, 100);
    // Generate initial sequence
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(vIniMax) + 1;
    }
    // Probability of update query
    double pUpdate = rnd.next(1, 9) / 10.0;
    struct Q { int type, x, y; };
    vector<Q> qs;
    int cntType2 = 0;
    for (int i = 0; i < M; i++) {
        if (rnd.next() < pUpdate) {
            // update: 1 i v
            int idx = rnd.next(1, N);
            int v = rnd.next(vUpdMax) + 1;
            qs.push_back({1, idx, v});
        } else {
            // query: 2 l r
            int l = rnd.next(1, N - 1);
            int r = rnd.next(l + 1, N);
            qs.push_back({2, l, r});
            cntType2++;
        }
    }
    // Ensure at least one type-2 query
    if (cntType2 == 0) {
        // force the first query to be type 2
        int l = rnd.next(1, N - 1);
        int r = rnd.next(l + 1, N);
        qs[0] = {2, l, r};
    }
    // Output
    println(N);
    println(A);
    println(M);
    for (auto &q : qs) {
        println(q.type, q.x, q.y);
    }
    return 0;
}
