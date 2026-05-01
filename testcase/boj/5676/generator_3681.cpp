#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases (concatenated, no leading T)
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Small sizes for hand-checkable cases
        int N = rnd.next(1, 10);
        int K = rnd.next(1, 20);
        println(N, K);
        // Hyper-parameter: allow zeros in initial array?
        bool allowZeroInit = rnd.next(0, 1);
        vector<int> X(N);
        for (int i = 0; i < N; i++) {
            if (allowZeroInit && rnd.next() < 0.3) {
                X[i] = 0;
            } else {
                int v = rnd.next(1, 100);
                int s = rnd.next(0, 1) ? 1 : -1;
                X[i] = v * s;
            }
        }
        // Print initial array
        println(X);
        // Hyper-parameter: ratio of product queries
        double P_ratio = rnd.next(2, 8) / 10.0;
        bool hasP = false;
        for (int qi = 0; qi < K; qi++) {
            bool isP;
            // Ensure at least one P
            if (qi == K - 1) {
                isP = !hasP;
            } else {
                isP = (rnd.next() < P_ratio);
            }
            if (isP) {
                int i = rnd.next(1, N);
                int j = rnd.next(i, N);
                println("P", i, j);
                hasP = true;
            } else {
                int i = rnd.next(1, N);
                // Hyper-parameter: allow zero in updates?
                bool allowZeroUpd = rnd.next(0, 1);
                int V;
                if (allowZeroUpd && rnd.next() < 0.3) {
                    V = 0;
                } else {
                    int v = rnd.next(1, 100);
                    int s = rnd.next(0, 1) ? 1 : -1;
                    V = v * s;
                }
                println("C", i, V);
            }
        }
    }
    return 0;
}
