#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of jobs
    int N = rnd.next(1, 10);

    // Setup time hyper-parameter
    double sp = rnd.next();
    int S;
    if (sp < 0.3) {
        S = 0;
    } else if (sp < 0.7) {
        S = rnd.next(1, 5);
    } else {
        S = rnd.next(5, 20);
    }

    // Range for processing times T_i
    int T_hi = rnd.next(5, 20);
    int T_lo = rnd.next(1, min(10, T_hi));

    // Range for cost factors F_i
    int F_hi = rnd.next(1, 20);
    int F_lo = rnd.next(1, F_hi);

    // Generate T_i with possible patterns
    int T_pattern = rnd.next(1, 3);
    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        T[i] = rnd.next(T_lo, T_hi);
    }
    if (T_pattern == 2) {
        sort(T.begin(), T.end());                        // non-decreasing
    } else if (T_pattern == 3) {
        sort(T.begin(), T.end(), greater<int>());        // non-increasing
    }

    // Generate F_i with possible correlation or patterns
    bool corr = rnd.next() < 0.3;  // correlate F to T occasionally
    int F_pattern = rnd.next(1, 3);
    vector<int> F(N);
    if (corr) {
        // Correlate F with T plus small noise
        for (int i = 0; i < N; i++) {
            int delta = rnd.next(-2, 2);
            int v = T[i] + delta;
            v = max(F_lo, min(F_hi, v));
            F[i] = v;
        }
    } else {
        for (int i = 0; i < N; i++) {
            F[i] = rnd.next(F_lo, F_hi);
        }
        if (F_pattern == 2) {
            sort(F.begin(), F.end());
        } else if (F_pattern == 3) {
            sort(F.begin(), F.end(), greater<int>());
        }
    }

    // Output the generated test case
    println(N);
    println(S);
    for (int i = 0; i < N; i++) {
        println(T[i], F[i]);
    }

    return 0;
}
