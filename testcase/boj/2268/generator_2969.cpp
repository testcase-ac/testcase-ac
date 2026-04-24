#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N and M for hand-checkable tests
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);
    // Ensure at least one Sum operation
    int S = rnd.next(1, M);
    // Build operation types: 0 = Sum, 1 = Modify
    vector<int> ops;
    ops.reserve(M);
    for (int i = 0; i < S; i++) ops.push_back(0);
    for (int i = 0; i < M - S; i++) ops.push_back(1);
    shuffle(ops.begin(), ops.end());
    // Hyper-parameter for modification value range
    int klvl = rnd.next(0, 2);
    int kmax = (klvl == 0 ? 10 : (klvl == 1 ? 100 : 100000));
    // Output header
    println(N, M);
    // Generate and print operations
    for (int t : ops) {
        if (t == 0) {
            // Sum(i, j)
            int i = rnd.next(1, N);
            int j = rnd.next(1, N);
            println(0, i, j);
        } else {
            // Modify(i, k)
            int i = rnd.next(1, N);
            int k = rnd.next(1, kmax);
            println(1, i, k);
        }
    }
    return 0;
}
