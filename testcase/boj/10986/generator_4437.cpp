#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N, M
    int N = rnd.next(1, 10);
    int M = rnd.next(2, 10);

    // Choose a scenario for diversity
    int scenario = rnd.next(0, 3);
    vector<long long> A(N);

    switch (scenario) {
        case 0:
            // All zeros
            for (int i = 0; i < N; i++)
                A[i] = 0;
            break;
        case 1:
            // Small values [0, M-1]
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(0, M - 1);
            break;
        case 2:
            // Large random values [0, 1e9]
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(0, 1000000000);
            break;
        case 3:
            // Mix of multiples of M and random residues
            for (int i = 0; i < N; i++) {
                if (rnd.next(0, 1) == 0) {
                    int t = rnd.next(0, 1000000000 / M);
                    A[i] = 1LL * t * M;
                } else {
                    A[i] = rnd.next(1, M - 1);
                }
            }
            break;
    }

    println(N, M);
    println(A);

    return 0;
}
