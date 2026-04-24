#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: small N and K
    int N = rnd.next(2, 10);
    int K = rnd.next(1, N);

    // Output N and K
    println(N, K);

    // Decide on global shape: sorted ascending, sorted descending, or random with repeats
    double shape = rnd.next();
    if (shape < 0.2) {
        // Ascending sequence
        int cur = rnd.next(0, 20);
        for (int i = 0; i < N; i++) {
            cur += rnd.next(0, 10);
            println(cur);
        }
    } else if (shape < 0.4) {
        // Descending sequence
        int cur = rnd.next(0, 20) + N * 10;
        for (int i = 0; i < N; i++) {
            cur -= rnd.next(0, 10);
            println(cur);
        }
    } else {
        // Random values with possible repeats
        int maxVal = rnd.next(0, 100);
        double dupProb = rnd.next();  // probability to repeat previous
        int prev = rnd.next(0, maxVal);
        println(prev);
        for (int i = 1; i < N; i++) {
            int v;
            if (rnd.next() < dupProb) {
                v = prev;
            } else {
                v = rnd.next(0, maxVal);
            }
            println(v);
            prev = v;
        }
    }

    return 0;
}
