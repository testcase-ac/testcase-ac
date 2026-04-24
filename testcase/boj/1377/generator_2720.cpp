#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small size for hand-checkable array
    int N = rnd.next(1, 10);
    println(N);
    // Hyper-parameter for different patterns
    double r = rnd.next();
    vector<int> A(N);
    if (r < 0.2) {
        // Fully sorted (strictly increasing)
        for (int i = 0; i < N; i++) A[i] = i;
    } else if (r < 0.4) {
        // Fully reverse-sorted
        for (int i = 0; i < N; i++) A[i] = N - i;
    } else if (r < 0.6) {
        // Almost sorted: start sorted then apply a few random swaps
        for (int i = 0; i < N; i++) A[i] = i;
        int swaps = rnd.next(1, max(1, N - 1));
        for (int k = 0; k < swaps; k++) {
            int p = rnd.next(0, N - 1);
            int q = rnd.next(0, N - 1);
            swap(A[p], A[q]);
        }
    } else if (r < 0.8) {
        // Many duplicates: small value range
        int maxv = rnd.next(0, 5);
        for (int i = 0; i < N; i++) A[i] = rnd.next(0, maxv);
    } else {
        // Completely random values in moderate range
        for (int i = 0; i < N; i++) A[i] = rnd.next(0, 100);
    }
    // Output each element on its own line
    for (int x : A) println(x);
    return 0;
}
