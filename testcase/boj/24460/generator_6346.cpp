#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide whether to generate small or larger N (but keep N<=16)
    bool small = rnd.next(0, 1) == 0;
    int m;
    if (small) {
        // Bias towards very small m (0..2)
        m = rnd.wnext(3, -2);  // samples [0..2], takes min of 3 samples
    } else {
        // Bias towards larger m (up to 4)
        m = rnd.wnext(5, 2);   // samples [0..4], takes max of 3 samples
    }
    int N = 1 << m;

    // Generate distinct raffle numbers 1..N*N and shuffle
    vector<int> vals(N * N);
    iota(vals.begin(), vals.end(), 1);
    shuffle(vals.begin(), vals.end());

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        vector<int> row(vals.begin() + i * N, vals.begin() + (i + 1) * N);
        println(row);
    }
    return 0;
}
