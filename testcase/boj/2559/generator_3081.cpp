#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for hand-checking
    int N = rnd.next(2, 10);
    // Bias K towards small, middle or large values
    vector<int> biases = {-1, 0, 1};
    int bias = rnd.any(biases);
    int K = rnd.wnext(N, bias) + 1; // yields 1..N with bias
    // Choose maximum absolute temperature
    vector<int> maxs = {5, 20, 100};
    int max_abs = rnd.any(maxs);
    // Pattern type: pure random, boosted positive segment, or many zeros
    int pattern = rnd.next(0, 2);
    vector<int> a(N);
    if (pattern == 0) {
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(-max_abs, max_abs);
    } else if (pattern == 1) {
        // random base then a positive run
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(-max_abs, max_abs);
        int L = rnd.next(1, N);
        int start = rnd.next(0, N - L);
        for (int i = start; i < start + L; i++)
            a[i] = rnd.next(max_abs/2, max_abs);
    } else {
        // mix zeros and random
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.3)
                a[i] = 0;
            else
                a[i] = rnd.next(-max_abs, max_abs);
        }
    }
    // Output
    println(N, K);
    println(a);
    return 0;
}
