#include "testlib.h"
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose even N with some bias: small or medium
    int N;
    int mode = rnd.next(0, 9);
    if (mode == 0) {
        N = 2;
    } else if (mode <= 2) {
        vector<int> small = {4, 6, 8};
        N = rnd.any(small);
    } else {
        int half = rnd.next(4, 10);  // 4..10
        N = half * 2;                // 8..20
    }

    // Generate base permutations
    vector<int> baseA(N), baseB(N);
    iota(baseA.begin(), baseA.end(), 1);
    iota(baseB.begin(), baseB.end(), 1);
    shuffle(baseA.begin(), baseA.end());
    shuffle(baseB.begin(), baseB.end());

    // Offsets to spread values across [1,1e9]
    int hiA = 1000000000 - N;
    int hiB = 1000000000 - N;
    int offsetA = rnd.next(1, hiA);
    int offsetB = rnd.next(1, hiB);

    // Build A and B arrays
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++) {
        A[i] = baseA[i] + offsetA;
        B[i] = baseB[i] + offsetB;
    }

    // Occasionally sort A or B to create edge patterns
    if (rnd.next(0, 9) == 0) {
        sort(A.begin(), A.end());
    } else if (rnd.next(0, 9) == 1) {
        sort(A.begin(), A.end(), greater<int>());
    }
    if (rnd.next(0, 9) == 0) {
        sort(B.begin(), B.end());
    } else if (rnd.next(0, 9) == 1) {
        sort(B.begin(), B.end(), greater<int>());
    }

    // Output
    println(N);
    println(A);
    println(B);

    return 0;
}
