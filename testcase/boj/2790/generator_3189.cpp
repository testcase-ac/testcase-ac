#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of drivers
    int N = rnd.next(3, 10);
    vector<int> B(N);

    // Maximum existing score
    int maxB = rnd.next(0, 20);

    // Choose distribution type for diversity
    int distType = rnd.next(0, 2);
    if (distType == 0) {
        // Uniform random scores
        for (int i = 0; i < N; i++) {
            B[i] = rnd.next(0, maxB);
        }
    } else if (distType == 1) {
        // Increasing baseline with small noise
        int step = maxB / N + 1;
        for (int i = 0; i < N; i++) {
            B[i] = i * step + rnd.next(0, step - 1);
        }
    } else {
        // Clustered scores around random centers
        int k = rnd.next(1, min(3, N));
        vector<int> centers(k);
        for (int i = 0; i < k; i++) {
            centers[i] = rnd.next(0, maxB);
        }
        int d = rnd.next(0, maxB / 4 + 1);
        for (int i = 0; i < N; i++) {
            B[i] = rnd.any(centers) + rnd.next(0, d);
        }
    }

    // Shuffle to randomize ordering
    shuffle(B.begin(), B.end());

    // Output
    println(N);
    for (int x : B) {
        println(x);
    }
    return 0;
}
