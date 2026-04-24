#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand-checkable
    int N = rnd.next(2, 10);
    vector<int> a(N);

    // Hyper-parameter: choose generation type
    int genType = rnd.next(0, 4);
    if (genType == 0) {
        // Fully random values in a small range
        int lo = rnd.next(-10, 0);
        int hi = rnd.next(0, 10);
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(lo, hi);
    } else if (genType == 1) {
        // Already sorted non-decreasing
        a[0] = rnd.next(-5, 5);
        for (int i = 1; i < N; i++)
            a[i] = a[i-1] + rnd.next(0, 3);
    } else if (genType == 2) {
        // Reverse sorted (strictly or with duplicates)
        a[0] = rnd.next(-5, 5) + 3 * N;
        for (int i = 1; i < N; i++)
            a[i] = a[i-1] - rnd.next(0, 3);
    } else if (genType == 3) {
        // Exactly one inversion: build sorted then inject drop
        a[0] = rnd.next(-5, 5);
        for (int i = 1; i < N; i++)
            a[i] = a[i-1] + rnd.next(0, 3);
        int idx = rnd.next(0, N-2);
        // Make a[idx] strictly greater than a[idx+1]
        a[idx] = a[idx+1] + rnd.next(1, 5);
    } else {
        // All elements equal
        int v = rnd.next(-5, 5);
        for (int i = 0; i < N; i++)
            a[i] = v;
    }

    // Output in problem format
    println(N);
    println(a);

    return 0;
}
