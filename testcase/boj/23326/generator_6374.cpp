#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of zones and queries
    int N = rnd.next(1, 20);
    int Q = rnd.next(1, 30);
    // Initial attractions
    vector<int> A(N);
    int initType = rnd.next(0, 2);
    if (initType == 0) {
        // all zeros
        fill(A.begin(), A.end(), 0);
    } else if (initType == 1) {
        // all ones
        fill(A.begin(), A.end(), 1);
    } else {
        // random with bias
        for (int i = 0; i < N; i++) {
            A[i] = (rnd.next() < 0.3 ? 1 : 0);
        }
    }
    // Output N, Q and initial A
    println(N, Q);
    println(A);

    // Ensure at least one type-3 query
    vector<int> qtype(Q, 0);
    int k3 = rnd.next(1, min(5, Q));
    vector<int> idx(Q);
    for (int i = 0; i < Q; i++) idx[i] = i;
    shuffle(idx.begin(), idx.end());
    for (int i = 0; i < k3; i++) {
        qtype[idx[i]] = 3;
    }

    for (int qi = 0; qi < Q; qi++) {
        if (qtype[qi] == 3) {
            println(3);
        } else {
            // choose type 1 or 2
            if (rnd.next(1, 2) == 1) {
                int i = rnd.next(1, N);
                println(1, i);
            } else {
                int x;
                if (rnd.next(0, 1) == 0) {
                    // small move
                    x = rnd.next(1, max(1, N * 3));
                } else {
                    // large move
                    x = rnd.next(1, 1000000000);
                }
                println(2, x);
            }
        }
    }
    return 0;
}
