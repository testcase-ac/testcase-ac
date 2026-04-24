#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    // Base probabilities
    double p1 = rnd.next(); // [0,1)
    double p2 = rnd.next();
    double p_low = min(p1, p2);
    double p_high = max(p1, p2);
    // Hotspot probabilities
    double p_hot = p_high + rnd.next() * (1.0 - p_high); // [p_high,1)
    // Choose hotspots
    int r_hot = rnd.next(1, N);
    int c_hot = rnd.next(1, M);
    // Build grid
    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            double p = p_low;
            if (i+1 == r_hot || j+1 == c_hot) p = p_hot;
            a[i][j] = (rnd.next() < p ? 1 : 0);
        }
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }
    return 0;
}
