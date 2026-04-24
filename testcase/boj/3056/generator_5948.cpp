#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of missions and agents
    int N = rnd.next(1, 20);
    // Choose pattern type for diversity
    int type = rnd.next(0, 4);
    vector<vector<int>> P(N, vector<int>(N));
    if (type == 0) {
        // Fully random probabilities
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                P[i][j] = rnd.next(0, 100);
    } else if (type == 1) {
        // Diagonal has higher success rates
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                P[i][j] = (i == j ? rnd.next(50, 100) : rnd.next(0, 50));
    } else if (type == 2) {
        // One row is dominant
        int r = rnd.next(0, N - 1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                P[i][j] = (i == r ? rnd.next(50, 100) : rnd.next(0, 50));
    } else if (type == 3) {
        // One column is dominant
        int c = rnd.next(0, N - 1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                P[i][j] = (j == c ? rnd.next(50, 100) : rnd.next(0, 50));
    } else {
        // Sparse matrix with many zeros
        double density = rnd.next(1, 100) / 100.0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                P[i][j] = (rnd.next() < density ? rnd.next(0, 100) : 0);
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++)
        println(P[i]);
    return 0;
}
