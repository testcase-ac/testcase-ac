#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(2, 10);
    int maxT = min(20, N * (N + 1) / 2);
    int T = rnd.next(1, maxT);

    // Hyper-parameters for array generation: random breakpoints for decrease/increase
    double t1 = rnd.next(0.0, 1.0);
    double t2 = rnd.next(0.0, 1.0);
    double th_lo = min(t1, t2), th_hi = max(t1, t2);

    // Build A with random non-decreasing/non-increasing/equal segments
    vector<int> A(N);
    A[0] = rnd.next(1, 10);
    for (int i = 1; i < N; i++) {
        double r = rnd.next();
        if (r < th_lo) {
            // decreasing step
            A[i] = max(1, A[i-1] - rnd.next(1, 3));
        } else if (r < th_hi) {
            // increasing step
            A[i] = A[i-1] + rnd.next(1, 3);
        } else {
            // equal step
            A[i] = A[i-1];
        }
    }

    // Generate T queries with diverse patterns
    vector<pair<int,int>> Q;
    for (int i = 0; i < T; i++) {
        int L, R;
        double r = rnd.next();
        if (r < 0.1) {
            // full range
            L = 1; R = N;
        } else if (r < 0.4) {
            // single point query
            L = R = rnd.next(1, N);
        } else if (r < 0.7) {
            // short subarray of length up to 5
            int len = rnd.next(2, min(5, N));
            L = rnd.next(1, N - len + 1);
            R = L + len - 1;
        } else {
            // random subarray
            L = rnd.next(1, N);
            R = rnd.next(L, N);
        }
        Q.emplace_back(L, R);
    }

    // Output
    println(N, T);
    println(A);
    for (auto &qr : Q) {
        println(qr.first, qr.second);
    }
    return 0;
}
