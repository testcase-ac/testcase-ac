#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of songs
    int N = rnd.next(1, 10);
    // Maximum volume
    int M = rnd.next(1, 20);
    // Starting volume
    int S = rnd.next(0, M);

    // Hyper-parameter for weighted sampling of differences
    // t > 0 biases to larger diffs, t < 0 biases to smaller diffs
    int t = rnd.next(-2, 2);

    vector<int> V;
    V.reserve(N);
    for (int i = 0; i < N; i++) {
        int d;
        // mix uniform and weighted sampling for diversity
        if (rnd.next(0, 9) < 3) {
            // uniform in [1, M]
            d = rnd.next(1, M);
        } else {
            // weighted in [0, M-1] then +1
            int x = rnd.wnext(M, t);
            d = x + 1;
            if (d > M) d = M;
        }
        V.push_back(d);
    }

    // Output in required format
    println(N, S, M);
    println(V);

    return 0;
}
