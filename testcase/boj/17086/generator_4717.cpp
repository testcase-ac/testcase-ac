#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int N = rnd.next(2, 10);
    int M = rnd.next(2, 10);
    int total = N * M;

    // Hyperparameter: decide how to choose number of sharks K
    bool useWeighted = rnd.next() < 0.5;
    int K;
    if (useWeighted) {
        // Weighted distribution: bias towards low or high counts
        int T = rnd.next(-3, 3);
        int raw = rnd.wnext(total, T); // in [0, total-1]
        K = raw;
        if (K < 1) K = 1;
        if (K > total - 1) K = total - 1;
    } else {
        // Uniform distribution
        K = rnd.next(1, total - 1);
    }

    // Prepare all cell indices and pick K unique positions for sharks
    vector<int> idx(total);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());
    vector<vector<int>> grid(N, vector<int>(M, 0));
    for (int i = 0; i < K; i++) {
        int d = idx[i];
        grid[d / M][d % M] = 1;
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(grid[i]);
    }
    return 0;
}
