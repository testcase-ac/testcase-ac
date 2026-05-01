#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sizes of arrays
    int n = rnd.next(1, 20);
    int m = rnd.next(1, 20);

    // Scales for element magnitudes
    vector<int> scales = {10, 100, 1000, 1000000};
    int scaleA = rnd.any(scales);
    int scaleB = rnd.any(scales);

    // Distribution types: 0=positive,1=mixed,2=sparse random,3=negative
    int typeA = rnd.next(0, 3);
    int typeB = rnd.next(0, 3);

    vector<int> A(n), B(m);
    for (int i = 0; i < n; i++) {
        switch (typeA) {
            case 0: A[i] = rnd.next(1, scaleA); break;
            case 1: A[i] = rnd.next(-scaleA, scaleA); break;
            case 2: A[i] = (rnd.next(0, 9) == 0 ? rnd.next(-scaleA, scaleA) : 0); break;
            case 3: A[i] = rnd.next(-scaleA, -1); break;
        }
    }
    for (int i = 0; i < m; i++) {
        switch (typeB) {
            case 0: B[i] = rnd.next(1, scaleB); break;
            case 1: B[i] = rnd.next(-scaleB, scaleB); break;
            case 2: B[i] = (rnd.next(0, 9) == 0 ? rnd.next(-scaleB, scaleB) : 0); break;
            case 3: B[i] = rnd.next(-scaleB, -1); break;
        }
    }

    // Compute a target T within realistic bounds
    long long sumA = accumulate(A.begin(), A.end(), 0LL);
    long long sumB = accumulate(B.begin(), B.end(), 0LL);
    long long bound = llabs(sumA) + llabs(sumB);
    long long maxT = max(100LL, bound);
    long long T = rnd.next(-maxT, maxT);

    // Output
    println(T);
    println(n);
    println(A);
    println(m);
    println(B);

    return 0;
}
