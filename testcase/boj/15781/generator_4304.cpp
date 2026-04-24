#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Choose a value bound for defense stats
    vector<int> choices = {10, 100, 1000, 1000000000};
    int R = rnd.any(choices);

    // Hyper-parameters for weighting distributions
    int th = rnd.next(-2, 2);
    int ta = rnd.next(-2, 2);

    // Generate helmet defenses
    vector<int> h(N);
    for (int i = 0; i < N; i++) {
        // rnd.wnext(R, th) gives [0, R-1] biased; +1 to shift to [1, R]
        h[i] = rnd.wnext(R, th) + 1;
    }
    // Generate vest defenses
    vector<int> a(M);
    for (int i = 0; i < M; i++) {
        a[i] = rnd.wnext(R, ta) + 1;
    }

    // Shuffle order to ensure randomness in positions
    shuffle(h.begin(), h.end());
    shuffle(a.begin(), a.end());

    // Output
    println(N, M);
    println(h);
    println(a);
    return 0;
}
