#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameters for sizes
    int n = rnd.next(3, 10);
    int l = rnd.next(2, min(n, 5));
    int m = rnd.next(2, 5);

    // Maximum possible sum W_k roughly m * l * max(T) * max(P)
    int maxW = m * l * 100 * 100;

    // Hyperparameters for distributions
    int T_mode = rnd.next(0, 2);
    int P_mode = rnd.next(0, 2);
    int W_mode = rnd.next(0, 2);

    // Generate path intensities T
    vector<vector<int>> T(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (T_mode == 0) {
                // uniform [0,100]
                T[i][j] = rnd.next(0, 100);
            } else if (T_mode == 1) {
                // mostly zeros
                T[i][j] = (rnd.next() < 0.7 ? 0 : rnd.next(1, 50));
            } else {
                // few high values
                T[i][j] = (rnd.next() < 0.7 ? rnd.next(0, 20) : rnd.next(80, 100));
            }
        }
    }

    // Generate telescope amplifications P
    vector<vector<int>> P(m, vector<int>(l));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < l; j++) {
            if (P_mode == 0) {
                // uniform [0,100]
                P[i][j] = rnd.next(0, 100);
            } else if (P_mode == 1) {
                // more zeros
                P[i][j] = (rnd.next() < 0.5 ? 0 : rnd.next(1, 50));
            } else {
                // few high
                P[i][j] = (rnd.next() < 0.7 ? rnd.next(0, 20) : rnd.next(80, 100));
            }
        }
    }

    // Choose threshold W based on hyperparameter
    int W;
    if (W_mode == 0) {
        // low threshold
        W = rnd.next(0, maxW / 3);
    } else if (W_mode == 1) {
        // medium
        W = rnd.next(maxW / 3, (maxW * 2) / 3);
    } else {
        // high
        W = rnd.next((maxW * 2) / 3, maxW);
    }

    // Output
    println(n, l, m, W);
    for (int i = 0; i < m; i++) {
        println(T[i]);
    }
    for (int i = 0; i < m; i++) {
        println(P[i]);
    }

    return 0;
}
