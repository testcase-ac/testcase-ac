#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand-checkable cases
    int N = rnd.next(1, 10);

    // base rank range around N
    int base = rnd.next(N, N + 5);
    // allow some extra spread for R_i
    int extra = rnd.next(0, 5);
    int bound = base + extra;  // R_i in [1..bound]

    // Tam's initial rank R
    int R = rnd.next(1, base);

    // Generate N subsequent ranks with mixed biases
    vector<int> seq;
    seq.reserve(N);
    for (int i = 0; i < N; i++) {
        double p = rnd.next();
        int x;
        if (p < 0.3) {
            // bias toward low ranks (strong contestants)
            x = rnd.wnext(bound, -1) + 1;
        } else if (p < 0.6) {
            // bias toward high ranks (weaker contestants)
            x = rnd.wnext(bound, 1) + 1;
        } else {
            // uniform
            x = rnd.next(1, bound);
        }
        seq.push_back(x);
    }

    // Output format
    println(R);
    println(N);
    println(seq);

    return 0;
}
