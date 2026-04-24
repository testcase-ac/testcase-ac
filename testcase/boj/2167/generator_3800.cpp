#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Value range hyper-parameter
    int maxVal = rnd.next(10, 100);

    // Generate 2D array
    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = rnd.next(-maxVal, maxVal);
        }
    }

    // Number of queries
    int maxK = min(20, N * M * 2);
    int K = rnd.next(1, maxK);

    // Hyper-parameters for query shapes
    double fullProb = rnd.next();   // probability of full array query
    double smallProb = rnd.next();  // probability of small query (~ up to 3x3)

    // Output sizes
    println(N, M);
    for (auto &row : a) {
        println(row);
    }
    println(K);

    // Generate queries
    for (int q = 0; q < K; q++) {
        double p = rnd.next();
        int i, j, x, y;
        if (p < fullProb) {
            // Full rectangle
            i = 1; j = 1; x = N; y = M;
        } else if (p < fullProb + smallProb) {
            // Small rectangle up to 3x3
            i = rnd.next(1, N);
            j = rnd.next(1, M);
            int di = rnd.next(0, min(2, N - i));
            int dj = rnd.next(0, min(2, M - j));
            x = i + di;
            y = j + dj;
        } else {
            // Random rectangle
            i = rnd.next(1, N);
            x = rnd.next(i, N);
            j = rnd.next(1, M);
            y = rnd.next(j, M);
        }
        println(i, j, x, y);
    }

    return 0;
}
