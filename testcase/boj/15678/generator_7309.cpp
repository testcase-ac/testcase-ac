#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 2 and 15 for readability
    int N = rnd.next(2, 15);

    // Choose D: sometimes minimal, sometimes maximal, else random
    int D;
    int dcase = rnd.next(1, 10);
    if (dcase <= 2) D = 1;
    else if (dcase <= 4) D = N - 1;
    else D = rnd.next(1, N - 1);

    // Scenario type for K values
    int t = rnd.next(0, 4);
    vector<long long> K(N);

    if (t == 0) {
        // All negative
        for (int i = 0; i < N; i++)
            K[i] = rnd.next(-100, -1);
    } else if (t == 1) {
        // All positive
        for (int i = 0; i < N; i++)
            K[i] = rnd.next(1, 100);
    } else if (t == 2) {
        // Mixed random
        for (int i = 0; i < N; i++)
            K[i] = rnd.next(-100, 100);
    } else if (t == 3) {
        // One big positive spike, rest non-positive
        for (int i = 0; i < N; i++)
            K[i] = rnd.next(-100, 0);
        int pos = rnd.next(0, N - 1);
        K[pos] = rnd.next(1, 1000);
    } else {
        // Alternating sign pattern
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) K[i] = rnd.next(1, 100);
            else K[i] = rnd.next(-100, -1);
        }
    }

    // Output
    println(N, D);
    println(K);

    return 0;
}
