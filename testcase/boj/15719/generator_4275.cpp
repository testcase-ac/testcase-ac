#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter t for weighted N selection bias
    vector<int> t_choices = {-2, -1, 0, 1, 2};
    int t = rnd.any(t_choices);
    // Generate N in [2..10] with bias
    int N = rnd.wnext(9, t) + 2;

    // Choose duplicate M in [1..N-1]
    int M = rnd.next(1, N - 1);

    // Build the array: numbers 1..N-1 once each, plus M again
    vector<int> a;
    a.reserve(N);
    for (int i = 1; i < N; ++i) a.push_back(i);
    a.push_back(M);

    // Three shuffling patterns for diversity
    double p = rnd.next();
    if (p < 0.3) {
        // leave almost sorted: duplicates at positions M-1 and N-1
    } else if (p < 0.6) {
        // full random shuffle
        shuffle(a.begin(), a.end());
    } else {
        // partial shuffle: split into two blocks
        int bs = rnd.next(1, N - 1);
        shuffle(a.begin(), a.begin() + bs);
        shuffle(a.begin() + bs, a.end());
    }

    // Output the test case
    println(N);
    println(a);

    return 0;
}
