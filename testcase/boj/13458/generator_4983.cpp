#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of exam rooms
    int N = rnd.next(1, 10);

    // Hyper-parameter: choose max bound for A_i from {10, 100, 1000}
    vector<int> maxOptions = {10, 100, 1000};
    int L = rnd.any(maxOptions);

    // Hyper-parameter for skewing A_i distribution: negative -> more small, positive -> more large
    int tA = rnd.next(-3, 3);

    // Generate A_i
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        // rnd.wnext(L, tA) in [0, L-1], +1 => [1, L]
        A[i] = 1 + rnd.wnext(L, tA);
    }

    // Hyper-parameters for B and C skew
    int tB = rnd.next(-2, 2);
    int tC = rnd.next(-2, 2);
    // Generate B, C in [1,20] with skew
    int B = 1 + rnd.wnext(20, tB);
    int C = 1 + rnd.wnext(20, tC);

    // Output
    println(N);
    println(A);
    println(B, C);

    return 0;
}
