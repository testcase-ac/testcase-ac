#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of values
    int N = rnd.next(2, 10);
    int total = N - 1;

    // Generate operator counts summing to total
    vector<int> ops(4, 0);
    if (rnd.next() < 0.3) {
        // heavy single operator
        int k = rnd.next(0, 3);
        ops[k] = total;
    } else {
        // random composition via cut points
        vector<int> cuts = {0, total};
        for (int i = 0; i < 3; i++) {
            cuts.push_back(rnd.next(0, total));
        }
        sort(cuts.begin(), cuts.end());
        for (int i = 0; i < 4; i++) {
            ops[i] = cuts[i+1] - cuts[i];
        }
    }

    // Value range hyper-parameters
    int lo, hi;
    if (rnd.next() < 0.2) {
        lo = 1; hi = 10;
    } else {
        lo = rnd.next(1, 50);
        hi = rnd.next(lo, 100);
    }
    // Shrink range if many multiplications to avoid overflow
    if (ops[2] > 4) {
        lo = 1;
        hi = min(hi, 3);
    } else if (ops[2] > 2) {
        lo = 1;
        hi = min(hi, 10);
    }
    if (lo > hi) lo = hi;

    // Generate the sequence A
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(lo, hi);
    }

    // Output
    println(N);
    println(A);
    println(ops[0], ops[1], ops[2], ops[3]);

    return 0;
}
