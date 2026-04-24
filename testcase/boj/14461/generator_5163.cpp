#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: sometimes biased larger, sometimes uniform
    int N;
    if (rnd.next(0, 1) == 0) {
        // biased towards larger values
        N = rnd.wnext(7, 1) + 3;  // range [3..10]
    } else {
        N = rnd.next(3, 10);
    }
    // Hyper-parameter for T: three modes
    int tType = rnd.next(0, 2);
    int T;
    if (tType == 0) {
        T = rnd.next(0, 10);
    } else if (tType == 1) {
        T = rnd.wnext(20, 1);
    } else {
        T = rnd.wnext(20, -1);
    }
    // Decide if we insert one very high-cost cell
    bool useHigh = rnd.next() < 0.3;
    int hi = -1, hj = -1;
    if (useHigh) {
        hi = rnd.next(0, N - 1);
        hj = rnd.next(0, N - 1);
    }
    // Generate grass-eating times
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (useHigh && i == hi && j == hj) {
                a[i][j] = rnd.next(50000, 100000);
            } else {
                // two modes per cell: uniform or weighted
                if (rnd.next(0, 1) == 0) {
                    a[i][j] = rnd.next(0, 100);
                } else {
                    int t = rnd.next(-2, 2);
                    a[i][j] = rnd.wnext(100, t);
                }
            }
        }
    }
    // Output
    println(N, T);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d%c", a[i][j], j + 1 == N ? '\n' : ' ');
        }
    }
    return 0;
}
